#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Property.h"
#include "ReadCSV.h"
#include "AStar.h"

// Comparator function for lower_bound to find closest price
bool comparePropertyPrice(const Property &prop, double price) {
    return prop.price < price;
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
    // std::string filename = "DSA Dataset.csv";
    std::string filename = "/Users/hemduttrao/Downloads/DSA Dataset-main.csv";

    std::vector<Property> properties = readCSV(filename);
    
    if (properties.empty()) {
        std::cerr << "Error: No properties loaded from the file.\n";
        return 1;
    }

    double currentLatitude, currentLongitude, targetPrice;
    std::cout << "Enter your current latitude and longitude: ";
    std::cin >> currentLatitude >> currentLongitude;
    std::cout << "Enter your target price: ";
    std::cin >> targetPrice;

    // Find the closest properties to the target price
    std::vector<Property>::iterator lowerBound = std::lower_bound(
        properties.begin(), properties.end(), targetPrice, comparePropertyPrice);

    // Collect 500 properties below or equal to the target price
    std::vector<Property> closestProperties;
    std::vector<Property>::iterator it = lowerBound;
    for (int i = 0; i < 500 && it != properties.begin(); ++i) {
        --it;
        closestProperties.push_back(*it);
    }

    // Collect 500 properties above or equal to the target price
    it = lowerBound;
    for (int i = 0; i < 500 && it != properties.end(); ++i, ++it) {
        closestProperties.push_back(*it);
    }

    if (closestProperties.size() < 2) {
        std::cerr << "Error: Not enough properties to perform pathfinding.\n";
        return 1;
    }

    // Perform A* search between first and last property in the filtered list
    Property start = closestProperties.front();
    Property goal = closestProperties.back();

    std::vector<Property> path = aStarSearch(start, goal, closestProperties);

    if (path.empty()) {
        std::cout << "No path found to the target property.\n";
    } else {
        std::cout << "Path found to target property:\n";
        for (const auto &prop : path) {
            std::cout << "Price: " << prop.price << ", Latitude: " << prop.latitude << ", Longitude: " << prop.longitude << "\n";
        }
    }

    // Save selected properties to a CSV file
    writeToCSV("Filtered_Properties.csv", closestProperties);

    std::cout << "Filtered properties saved to 'Filtered_Properties.csv'." << std::endl;

    return 0;
}
 