#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Property.h"
#include "ReadCSV.h"

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
    
    // Print the first 10 properties or all if less than 10
    size_t limit = std::min(static_cast<size_t>(10), properties.size());
    for (size_t i = 0; i < limit; ++i) {
        std::cout << "Property " << (i + 1) << ": "
                  << "Price: " << properties[i].price << ", "
                  << "Latitude: " << properties[i].latitude << ", "
                  << "Longitude: " << properties[i].longitude << std::endl;
    }

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

    // Save selected properties to a CSV file
    writeToCSV("Filtered_Properties.csv", closestProperties);

    std::cout << "Filtered properties saved to 'Filtered_Properties.csv'." << std::endl;
    return 0;
}
