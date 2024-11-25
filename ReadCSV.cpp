// ReadCSV.cpp
#include "ReadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Property> readCSV(const std::string &filename) {
    std::vector<Property> properties;
    std::ifstream file(filename);
    std::string line, word;

    if (file.is_open()) {
        std::getline(file, line);  // Skip the header line

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Property property;

            // // Skip the first column (property number)
            // std::getline(ss, word, ',');
          
            std::getline(ss, word, ',');
            property.price = std::stod(word);

            std::getline(ss, word, ',');
            property.latitude = std::stod(word);

            std::getline(ss, word, ',');
            property.longitude = std::stod(word);

            properties.push_back(property);
        }
        file.close();
    } else {
        std::cerr << "Error: Could not open the file.\n";
    }

    return properties;
}
