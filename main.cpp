#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Property.h"
#include "ReadCSV.h"
#include "AStar.h"
#include "Haversine.h"

// Comparator function for lower_bound to find closest price
bool comparePropertyPrice(const Property &prop, double price) {
    return prop.price < price;
}

bool isInSaudiArabia(double latitude, double longitude) {
    return (latitude >= 16.0 && latitude <= 32.5 &&
            longitude >= 34.5 && longitude <= 55.7);
}

// Function to save selected properties to CSV
void writeToCSV(const std::string &filename, const std::vector<Property> &properties) {
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

    std::cout << "The program finds the best property" << 
    "by distance and price in Saudi Arabia's prospering"<< 
    "areas using the A* and Dijkstras algorithm \n";

    double currentLatitude, currentLongitude, targetPrice;
    std::cout << "\n Enter your current latitude and longitude"<<
    "in Saudi Arabia latitude between 16.0 & 32.5 "<<
     "and longitude between 34.5 & 55.7: ";
    std::cin >> currentLatitude >> currentLongitude;

        if (!isInSaudiArabia(currentLatitude, currentLongitude)) {
        std::cerr << "Error: Location is outside Saudi Arabia. "<<
    "Please enter valid coordinates within Saudi Arabia.\n";
        return 1;
    }

    std::cout << "Enter your target price: ";
    std::cin >> targetPrice;

    // Find the closest properties to the target price
    std::vector<Property>::iterator lowerBound = std::lower_bound(
        properties.begin(), properties.end(), targetPrice, comparePropertyPrice);

        // Calculate a combined score for each property and sort
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
        return 1;
    }


    // Perform A* search using the updated algorithm
    std::vector<Property> path = aStarSearch(currentLatitude, currentLongitude, targetPrice, closestProperties);

    if (path.empty()) {
        std::cout << "No path found to the target property.\n";
    } else {
        // std::cout << "A* Path found to target property:\n";
            const Property& startNode = path.front();
    std::cout << "\nUser's Position:\n";
    std::cout << "Price: " << startNode.price << ", Latitude: " << startNode.latitude << ", Longitude: " << startNode.longitude << "\n\n";

    // Print final destination
    const Property& finalNode = path.back();
    std::cout << "Final Destination Found A* by:\n";
    std::cout << "Price: " << finalNode.price << ", Latitude: " << finalNode.latitude << ", Longitude: " << finalNode.longitude << "\n\n";

    // Print the entire path
    // std::cout << "A* Path Begin:\n";
    // for (size_t i = 0; i < path.size(); ++i) {
    //     std::cout << "Price: " << path[i].price
    //               << ", Latitude: " << path[i].latitude
    //               << ", Longitude: " << path[i].longitude;
    //     if (i == path.size() - 1) {
    //         std::cout << " (Final Node)";
    //     }
    //     std::cout << "\n";
    // }
    }
    // Save selected properties to a CSV file
    writeToCSV("Filtered_Properties.csv", closestProperties);

    std::cout << "Filtered properties saved to 'Filtered_Properties.csv'." << std::endl;

    return 0;
}
 