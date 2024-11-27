#include "AStar.h"
#include "Haversine.h"
#include <unordered_map>
#include <set>
#include <cmath>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>

#include <map>

std::map<std::string, std::vector<std::string>> cityMap;  // Map to store city names

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

std::vector<Property> aStarSearch(double startLat, double startLon, double targetPrice, const std::vector<Property>& properties) {
    
    auto startTime = std::chrono::high_resolution_clock::now();

    // Priority queue to store nodes to explore
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::unordered_map<int, Node> allNodes;  // Map nodes by ID
    std::set<int> closedSet;  // To avoid revisiting nodes

    // Step 1: Find the closest node to the virtual start
    double minDistance = std::numeric_limits<double>::max();
    int closestNodeIndex = -1;

    auto step1Start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < properties.size(); ++i) {
        double dist = haversine(startLat, startLon, properties[i].latitude, properties[i].longitude);
        if (dist < minDistance) {
            minDistance = dist;
            closestNodeIndex = static_cast<int>(i);
        }
    }

    auto step1End = std::chrono::high_resolution_clock::now();

    if (closestNodeIndex == -1) {
        return {};  // No valid nodes found
    }

    // Step 2: Add the closest node as the starting point
    Property virtualStart = {0.0, startLat, startLon};  // Dummy price 0.0
    Node startNode = {closestNodeIndex, minDistance, 
        std::abs(properties[closestNodeIndex].price - targetPrice), 
        properties[closestNodeIndex], 
        nullptr};
    openSet.push(startNode);
    allNodes[closestNodeIndex] = startNode;

    Node bestGoalNode;
    bool goalFound = false;

    auto step2End = std::chrono::high_resolution_clock::now();

    auto step3Start = std::chrono::high_resolution_clock::now();

    // Step 3: A* Search
    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        // Update best goal node
        if (!goalFound || std::abs(current.property.price - targetPrice) < std::abs(bestGoalNode.property.price - targetPrice)) {
            bestGoalNode = current;
            goalFound = true;
        }
        closedSet.insert(current.id);

        // Expand neighbors
        // for (size_t i = 0; i < properties.size(); ++i) {
        //     if (closedSet.count(i)) continue;

    for (size_t i = 0; i < properties.size(); ++i) {
        if (closedSet.count(i)) {
            // std::cout << "  Skipping Node " << i << " (Already Visited)\n";
            continue;
        }

            double tentativeGCost = current.gCost + haversine(current.property.latitude, current.property.longitude, properties[i].latitude, properties[i].longitude);
            double hCost = std::abs(properties[i].price - targetPrice) + haversine(properties[i].latitude, properties[i].longitude, startLat, startLon);

    Node neighbor = {static_cast<int>(i), tentativeGCost, hCost, properties[i], &allNodes[current.id]};
    
            if (!allNodes.count(i) || tentativeGCost < allNodes[i].gCost) {
                openSet.push(neighbor);
                allNodes[i] = neighbor;
            } 
        }
    }

        auto step3End = std::chrono::high_resolution_clock::now();


    // Step 4: Reconstruct the path

    auto step4Start = std::chrono::high_resolution_clock::now();

    std::vector<Property> path;
    Node* currentNode = &bestGoalNode;

    while (currentNode != nullptr) {
        path.push_back(currentNode->property);
        currentNode = currentNode->parent;
    }

    // Include the virtual start for completeness
    path.push_back(virtualStart);
    std::reverse(path.begin(), path.end());

    auto step4End = std::chrono::high_resolution_clock::now();

    auto endTime = std::chrono::high_resolution_clock::now();

    // Print time breakdown
    std::cout << "Time Breakdown (in microseconds):\n";
    std::cout << "Step 1 (Find Closest Node): " 
              << std::chrono::duration_cast<std::chrono::microseconds>(step1End - step1Start).count() << "µs\n";
    std::cout << "Step 2 (Initialize Start Node): " 
              << std::chrono::duration_cast<std::chrono::microseconds>(step2End - step1End).count() << "µs\n";
    std::cout << "Step 3 (A* Search Loop): " 
              << std::chrono::duration_cast<std::chrono::microseconds>(step3End - step3Start).count() << "µs\n";
    std::cout << "Step 4 (Reconstruct Path): " 
              << std::chrono::duration_cast<std::chrono::microseconds>(step4End - step4Start).count() << "µs\n";
    std::cout << "Total Time: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "µs\n";

    // Clear previous data in the cityMap
    cityMap.clear();

           std::cout << "\n A* Path :\n";
    for (size_t i = 0; i < path.size(); ++i) {
         std::string cityName = getCityName(path[i].latitude, path[i].longitude);
        path[i].cityName = cityName;  // Add city name to the property

        // Add city to the map
        if (i == 0) {
            cityMap["start"].push_back(cityName);  // Start city
        } else if (i == path.size() - 1) {
            cityMap["end"].push_back(cityName);  // End city
        } else {
            cityMap["intermediary"].push_back(cityName);  // Intermediary cities
        }
        std::cout << "City: " << cityName
                  << ", Price: " << path[i].price
                  << ", Latitude: " << path[i].latitude
                  << ", Longitude: " << path[i].longitude << "\n";
    }

// for (const auto& city : cityMap["intermediary"]) {
//     std::cout << "Intermediary City: " << city << "\n";
// }
    return path;
}
