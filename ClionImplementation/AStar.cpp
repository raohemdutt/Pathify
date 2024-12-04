#include "AStar.h"
#include "Haversine.h"
#include "Utilities.h"
#include <unordered_map>
#include <set>
#include <cmath>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>


#include <map>

//add memeory implmentation here 
std::tuple<std::vector<Property>, TimingInfo, MemoryInfo> aStarSearch(double startLat, double startLon, double targetPrice, const std::vector<Property>& properties) {
    
    auto startTime = std::chrono::high_resolution_clock::now();

    size_t memoryOpenSet = 0;      // Memory used by the priority queue
    size_t memoryAllNodes = 0;     // Memory used by all nodes map
    size_t memoryClosedSet = 0;    // Memory used by the closed set

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


    memoryOpenSet = sizeof(Node) * openSet.size(); // Memory for the priority queue
    memoryAllNodes = sizeof(Node) * allNodes.size(); // Memory for the nodes map


    Node bestGoalNode;
    bool goalFound = false;

    auto step2End = std::chrono::high_resolution_clock::now();

    auto step3Start = std::chrono::high_resolution_clock::now();

    // Step 3: A* Search
    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        memoryOpenSet = sizeof(Node) * openSet.size();  // Update memory usage for openSet

        // Update best goal node
        if (!goalFound || std::abs(current.property.price - targetPrice) < std::abs(bestGoalNode.property.price - targetPrice)) {
            bestGoalNode = current;
            goalFound = true;
        }
        closedSet.insert(current.id);
        memoryClosedSet = sizeof(int) * closedSet.size();  // Update memory usage for closedSet

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
                
                memoryOpenSet = sizeof(Node) * openSet.size();  // Update memory for openSet
                memoryAllNodes = sizeof(Node) * allNodes.size();  // Update memory for allNodes

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
    TimingInfo timings;
    timings.step1Time = std::chrono::duration_cast<std::chrono::microseconds>(step1End - step1Start).count();
    timings.step2Time = std::chrono::duration_cast<std::chrono::microseconds>(step2End - step1End).count();
    timings.step3Time = std::chrono::duration_cast<std::chrono::microseconds>(step3End - step3Start).count();
    timings.step4Time = std::chrono::duration_cast<std::chrono::microseconds>(step4End - step4Start).count();
    timings.totalTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

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

    // Print memory breakdown
    std::cout << "\nMemory Breakdown (in bytes):\n";
    std::cout << "Priority Queue (Open Set): " << memoryOpenSet << " bytes\n";
    std::cout << "All Nodes Map: " << memoryAllNodes << " bytes\n";
    std::cout << "Closed Set: " << memoryClosedSet << " bytes\n";
    std::cout << "Total Memory Usage: "
              << memoryOpenSet + memoryAllNodes + memoryClosedSet << " bytes\n";

    MemoryInfo memoryInfo;
    memoryInfo.memoryOpenSet = memoryOpenSet;
    memoryInfo.memoryAllNodes = memoryAllNodes;
    memoryInfo.memoryClosedSet = memoryClosedSet;
    memoryInfo.memoryTotal = memoryOpenSet + memoryAllNodes + memoryClosedSet;

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
    return {path, timings, memoryInfo};
}
