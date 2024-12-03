#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Property.h"
#include "ReadCSV.h"
#include "AStar.h"
#include "Haversine.h"
#include "Dijkstras.cpp"
#include "crow_all.h"

// Comparator function for lower_bound to find closest price
bool comparePropertyPrice(const Property &prop, double price) {
    return prop.price < price;
}

// Function to save selected properties to CSV
void writeToCSV(const std::string &filename, std::vector<Property> &properties) {
    std::ofstream file(filename);
    file << "Price,Latitude,Longitude\n";  // CSV header

    for (size_t i = 0; i < properties.size(); ++i) {
        file << properties[i].price << ","
             << properties[i].latitude << ","
             << properties[i].longitude << "\n";
    }
    file.close();
}

int main() {
    std::string filename = "Processed_DSA_Dataset.csv";
    // std::string filename = "/Users/hemduttrao/Downloads/DSA Dataset-main.csv";

    std::vector<Property> properties = readCSV(filename);
    
    if (properties.empty()) {
        std::cerr << "Error: No properties loaded from the file.\n";
        return 1;
    }

    //Start Crow Server:
    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global().origin("*");


    //To access data from the query string (e.g., https://example.com/process?lat=20&lng=22&price=2000), use req.url_params:
    CROW_ROUTE(app, "/")([](){
            return "Hello world";
    });


    //Example to call: http://0.0.0.0:8008/process?lat=20&lng=22&price=2000&type=a use this to TEST!!!
    CROW_ROUTE(app, "/process")([properties](const crow::request& req)->crow::response{
        crow::json::wvalue crowResponse;
        std::string lat = req.url_params.get("lat");
        std::string lng = req.url_params.get("lng");
        std::string price = req.url_params.get("price");
        std::string type = req.url_params.get("type");
        double currentLatitude = strtod(lat.c_str(), nullptr);
        double currentLongitude = strtod(lng.c_str(), nullptr);
        double targetPrice = strtod(price.c_str(), nullptr);

        std::cout << "Running Processing with Lat: "<<currentLatitude<<" Lng: "<<currentLongitude<<" Price: "<<targetPrice<<std::endl;
        // Find the closest properties to the target price
        std::vector<Property>::const_iterator lowerBound = std::lower_bound(
        properties.begin(), properties.end(), targetPrice, comparePropertyPrice);

        std::vector<std::pair<double, Property>> scoredProperties;
        for (const auto& prop : properties) {
            double priceDiff = std::abs(prop.price - targetPrice);
            double geoDist = haversine(currentLatitude, currentLongitude, prop.latitude, prop.longitude);
            double score = priceDiff + geoDist;  // Combined metric: price proximity + distance
            scoredProperties.emplace_back(score, prop);
        }

            // Sort by the combined score (lowest score = best match)
        std::sort(scoredProperties.begin(), scoredProperties.end(), [](const std::pair<double, Property>& a, const std::pair<double, Property>& b) {
           return a.first < b.first;  // Sort by score
        });
        // // Sort properties by price for efficient filtering
        // std::sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        //     return a.price < b.price;
        // });

        // Select the top 10000 closest properties based on the combined score
        std::vector<Property> closestProperties;
        for (size_t i = 0; i < 10000 && i < scoredProperties.size(); ++i) {
            closestProperties.push_back(scoredProperties[i].second);
        }

        if (closestProperties.size() < 2) {
            std::cerr << "Error: Not enough properties to perform pathfinding.\n";
            crow::json::wvalue error_response;
            error_response["error"] = "Not enough properties to perform pathfinding.";
            return crow::response(400, error_response);
        }

        auto dijkstraStart = std::chrono::high_resolution_clock::now();
        //std::vector<Property> dijkstraPath = dijkstras(currentLatitude, currentLongitude, targetPrice, closestProperties);
        auto dijkstraEnd = std::chrono::high_resolution_clock::now();
        auto dseconds = std::chrono::duration_cast<std::chrono::milliseconds>(dijkstraEnd - dijkstraStart);
        // Perform A* search using the updated algorithm
        std::tuple<std::vector<Property>, TimingInfo> result = aStarSearch(currentLatitude, currentLongitude, targetPrice, closestProperties);
        std::vector<Property> path = std::get<0>(result);
        TimingInfo timings = std::get<1>(result);


        if (path.empty()) {
        std::cout << "No path found to the target property.\n";
        }
        else {
            std::cout << "A* Path found to target property:\n";
            const Property& startNode = path.front();
            std::cout << "User's Position:\n";
            std::cout << "Price: " << startNode.price << ", Latitude: " << startNode.latitude << ", Longitude: " << startNode.longitude << "\n\n";
            // Print final destination
           const Property& finalNode = path.back();
           std::cout << "Final Destination Found A* by:\n";
           std::cout << "Price: " << finalNode.price << ", Latitude: " << finalNode.latitude << ", Longitude: " << finalNode.longitude << "\n\n";

           // Print the entire path
           std::cout << "A* Path Begin:\n";
           for (size_t i = 0; i < path.size(); ++i) {
               std::cout << "Price: " << path[i].price
                         << ", Latitude: " << path[i].latitude
                         << ", Longitude: " << path[i].longitude<< ", City: " << path[i].cityName;
               if (i == path.size() - 1) {
                   std::cout << " (Final Node)";
               }
               std::cout << "\n";
           }
            //Create an array of objects with a price, longitude and latitude
            if(type == "a") {
                crow::json::wvalue::list pathJson;
                for (size_t i = 0; i < path.size(); ++i) {
                    crow::json::wvalue propertyJson;
                    propertyJson["price"] = path[i].price;
                    propertyJson["latitude"] = path[i].latitude;
                    propertyJson["longitude"] = path[i].longitude;
                    propertyJson["step1micros"] = timings.step1Time;
                    propertyJson["step2micros"] = timings.step2Time;
                    propertyJson["step3micros"] = timings.step3Time;
                    propertyJson["step4micros"] = timings.step4Time;
                    propertyJson["totalmicros"] = timings.totalTime;
                    if (i == 0) {
                        propertyJson["type"] = "start";
                    } else if (i == path.size() - 1) {
                        propertyJson["type"] = "end";
                    } else {
                        propertyJson["type"] = "intermediate";
                    }
                    pathJson.push_back(std::move(propertyJson));
                }
                crowResponse["path"] = std::move(pathJson);
            }
/*
 *To Fix
            if(type == "d") {
                //do dijkstras
                crow::json::wvalue::list pathJson;
                for (size_t i = 0; i < dijkstraPath.size(); ++i) {
                    crow::json::wvalue propertyJson;
                    propertyJson["price"] = dijkstraPath[i].price;
                    propertyJson["latitude"] = dijkstraPath[i].latitude;
                    propertyJson["longitude"] = dijkstraPath[i].longitude;
                    propertyJson["seconds"] = dseconds.count();
                    if (i == 0) {
                        propertyJson["type"] = "start";
                    } else if (i == path.size() - 1) {
                        propertyJson["type"] = "end";
                    } else {
                        propertyJson["type"] = "intermediate";
                    }
                    pathJson.push_back(std::move(propertyJson));
                }
                crowResponse["path"] = std::move(pathJson);
            }

*/




        }
        // Save selected properties to a CSV file
        writeToCSV("Filtered_Properties.csv", closestProperties);
        std::cout << "Filtered properties saved to 'Filtered_Properties.csv'." << std::endl;
        return crow::response(crowResponse);
    });



    app.port(8008).multithreaded().run();
    return 0;


}
 