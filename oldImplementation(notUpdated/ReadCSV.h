// ReadCSV.h
#pragma once
#include <vector>
#include <string>
#include "Property.h"

// Function to read a CSV file and return a vector of Property structs
std::vector<Property> readCSV(const std::string &filename);

