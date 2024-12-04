#include "Utilities.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

// Initialize the shared city map
std::map<std::string, std::vector<std::string>> cityMap;

std::string getCityName(double latitude, double longitude) {
    std::string command = "python3 reverse_geocode.py " +
                          std::to_string(latitude) + " " +
                          std::to_string(longitude);
    char buffer[128];
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run Python script.\n";
        return "Unknown";
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    // Trim the output (if necessary)
    result.erase(result.find_last_not_of(" \n\r\t") + 1);
    return result;
}

void clearCityMap() {
    cityMap.clear();
}
