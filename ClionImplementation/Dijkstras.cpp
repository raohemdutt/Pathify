#include "Dijkstras.h"
#include "Haversine.h"
#include "Utilities.h"
#include <unordered_map>
#include <set>
#include <cmath>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iostream>

std::tuple<std::vector<Property>, TimingInfo> dijkstraShortestPath(double startLat, double startLon, const std::vector<Property>& properties) {
    auto startTime = std::chrono::high_resolution_clock::now();

    // Priority queue to store nodes to explore
    std::priority_queue<DijkstraNode, std::vector<DijkstraNode>, std::greater<DijkstraNode>> openSet;
    std::unordered_map<int, DijkstraNode> allNodes;  // Map nodes by ID
    std::set<int> closedSet;  // To avoid revisiting nodes
    // Before running the algorithm
    clearCityMap();

    // Memory tracking
    size_t memoryOpenSet = 0;      // Memory used by the priority queue
    size_t memoryAllNodes = 0;     // Memory used by all nodes
    size_t memoryClosedSet = 0;    // Memory used by the closed set

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

    // Step 2: Initialize the start node
    Property virtualStart = {0.0, startLat, startLon};  // Dummy price 0.0
    DijkstraNode startNode = {properties[closestNodeIndex], 0.0, nullptr};
    openSet.push(startNode);
    allNodes[closestNodeIndex] = startNode;

    memoryOpenSet += sizeof(DijkstraNode) * openSet.size();
    memoryAllNodes += sizeof(DijkstraNode) * allNodes.size();

    auto step2End = std::chrono::high_resolution_clock::now();

    auto step3Start = std::chrono::high_resolution_clock::now();

    // Step 3: Dijkstra's algorithm
    std::shared_ptr<DijkstraNode> bestGoalNode = nullptr;

    while (!openSet.empty()) {
        DijkstraNode current = openSet.top();
        openSet.pop();

        memoryOpenSet = sizeof(DijkstraNode) * openSet.size();  // Update memory usage for openSet
        closedSet.insert(current.id);

        memoryClosedSet = sizeof(int) * closedSet.size();  // Update memory usage for closedSet

        // Expand neighbors
        for (size_t i = 0; i < properties.size(); ++i) {
            if (closedSet.count(i)) continue;

            double tentativeGCost = current.g_cost + haversine(
                current.property.latitude, current.property.longitude,
                properties[i].latitude, properties[i].longitude);

            // DijkstraNode neighbor = {properties[i], tentativeGCost, std::make_shared<DijkstraNode>(current)};
            auto parentPtr = std::make_shared<DijkstraNode>(current.property, current.g_cost, current.parent);
            DijkstraNode neighbor = {properties[i], tentativeGCost, parentPtr};

            if (!allNodes.count(i) || tentativeGCost < allNodes[i].g_cost) {
                allNodes[i] = neighbor;
                openSet.push(neighbor);

                memoryOpenSet = sizeof(DijkstraNode) * openSet.size();  // Update memory for openSet
                memoryAllNodes = sizeof(DijkstraNode) * allNodes.size();  // Update memory for allNodes

                // Update the goal node if this path is better
                if (!bestGoalNode || neighbor.g_cost < bestGoalNode->g_cost) {
                    bestGoalNode = std::make_shared<DijkstraNode>(neighbor);
                }
            }
        }
    }

    auto step3End = std::chrono::high_resolution_clock::now();

    // Step 4: Reconstruct the path
    auto step4Start = std::chrono::high_resolution_clock::now();

    std::vector<Property> path;
    while (bestGoalNode != nullptr) {
                // Get the city name for the property
        std::string cityName = getCityName(bestGoalNode->property.latitude, bestGoalNode->property.longitude);
        bestGoalNode->property.cityName = cityName;

        // Add city to the cityMap
        if (bestGoalNode->parent == nullptr) {
            cityMap["start"].push_back(cityName);
        } else if (bestGoalNode->parent->parent == nullptr) {
            cityMap["end"].push_back(cityName);
        } else {
            cityMap["intermediary"].push_back(cityName);
        }


        path.push_back(bestGoalNode->property);
        bestGoalNode = bestGoalNode->parent;
    }

    std::string virtualStartCityName = getCityName(startLat, startLon);
    virtualStart.cityName = virtualStartCityName;
    cityMap["start"].push_back(virtualStartCityName);
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


    // Time and memory analysis
    std::cout << "Time Breakdown (in microseconds):\n";
    std::cout << "Step 1 (Find Closest Node): "
              << std::chrono::duration_cast<std::chrono::microseconds>(step1End - step1Start).count() << "µs\n";
    std::cout << "Step 2 (Initialize Start Node): "
              << std::chrono::duration_cast<std::chrono::microseconds>(step2End - step1End).count() << "µs\n";
    std::cout << "Step 3 (Dijkstra Search Loop): "
              << std::chrono::duration_cast<std::chrono::microseconds>(step3End - step3Start).count() << "µs\n";
    std::cout << "Step 4 (Reconstruct Path): "
              << std::chrono::duration_cast<std::chrono::microseconds>(step4End - step4Start).count() << "µs\n";
    std::cout << "Total Time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "µs\n";

    std::cout << "\nMemory Breakdown (in bytes):\n";
    std::cout << "Priority Queue (Open Set): " << memoryOpenSet << " bytes\n";
    std::cout << "All Nodes Map: " << memoryAllNodes << " bytes\n";
    std::cout << "Closed Set: " << memoryClosedSet << " bytes\n";
    std::cout << "Total Memory Usage: "
              << memoryOpenSet + memoryAllNodes + memoryClosedSet << " bytes\n";

    // Print path with city names
    std::cout << "\nDijkstra Path:\n";
    for (const auto& prop : path) {
        std::cout << "City: " << prop.cityName
                  << ", Price: " << prop.price
                  << ", Latitude: " << prop.latitude
                  << ", Longitude: " << prop.longitude << "\n";
    }

    return {path, timings};
}
