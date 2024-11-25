#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

struct Property {
    double price;
    double latitude;
    double longitude;
};

// Function to read the dataset from a CSV file
std::vector<Property> readCSV(const std::string& filename) {
    std::vector<Property> properties;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << '\n';
        return properties;
    }

    std::string line;
    // Skip the header row
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string emptyColumn, priceStr, latStr, lngStr;

        // Read the columns, skipping the empty one
        if (std::getline(ss, emptyColumn, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, latStr, ',') &&
            std::getline(ss, lngStr, ',')) {
            Property property;
            property.price = std::stod(priceStr);
            property.latitude = std::stod(latStr);
            property.longitude = std::stod(lngStr);
            properties.push_back(property);
        }
    }

    file.close();
    return properties;
}

// Function to write the dataset to a new CSV file
void writeCSV(const std::string& filename, const std::vector<Property>& properties) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << '\n';
        return;
    }

    // Write the header row
    file << "Price,Latitude,Longitude\n";

    for (size_t i = 0; i < properties.size(); ++i) {
        const Property& property = properties[i];
        file << property.price << ',' << property.latitude << ',' << property.longitude << '\n';
    }

    file.close();
}

// Comparator function for sorting
bool compareByPrice(const Property& a, const Property& b) {
    return a.price < b.price;
}

// Function to preprocess the dataset and ensure unique prices
void preprocessDataset(std::vector<Property>& properties) {
    // Sort properties by price
    std::sort(properties.begin(), properties.end(), compareByPrice);

    // Use a set to track unique prices
    std::set<double> uniquePrices;

    for (size_t i = 0; i < properties.size(); ++i) {
        double originalPrice = properties[i].price;
        int k = 1;  // Start quadratic probing

        // Keep probing until a truly unique price is found
        while (uniquePrices.count(properties[i].price) > 0) {
            properties[i].price = originalPrice + 0.01 * k * k;  // Adjust price
            k++;
        }

        // Add the unique price to the set
        uniquePrices.insert(properties[i].price);
    }
}

int main() {
    // Input and output file names
    std::string inputFile = "/Users/hemduttrao/Downloads/DSA Dataset-main.csv";
    std::string outputFile = "Processed_DSA_Dataset.csv";
    // Read the dataset
    std::vector<Property> properties = readCSV(inputFile);

    if (properties.empty()) {
        std::cerr << "Error: No data to process.\n";
        return 1;
    }

    std::cout << "Dataset loaded. Processing " << properties.size() << " entries...\n";

    // Preprocess the dataset
    preprocessDataset(properties);

    // Write the processed dataset
    writeCSV(outputFile, properties);

    std::cout << "Processed dataset saved to " << outputFile << ".\n";

    return 0;
}
