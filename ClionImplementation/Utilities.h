#pragma once
#include <string>
#include <vector>
#include <map>

// Declare the shared city map
extern std::map<std::string, std::vector<std::string>> cityMap;

// Declare the getCityName function
std::string getCityName(double latitude, double longitude);

// Utility function to clear the city map (optional)
void clearCityMap();
