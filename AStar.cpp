// // AStar.cpp
// #include "AStar.h"
// #include "Haversine.h"
// #include <unordered_map>
// #include <set>
// #include <cmath>

// std::vector<Property> aStarSearch(const Property& start, const Property& goal, const std::vector<Property>& properties) {
//     std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
//     std::unordered_map<int, Node> allNodes;  // Track nodes by ID for efficient access

//     // Initialize the start node
//     Node startNode = {0, 0.0, haversine(start.latitude, start.longitude, goal.latitude, goal.longitude), start, nullptr};
//     openSet.push(startNode);
//     allNodes[0] = startNode;

//     // A set of closed nodes to avoid revisiting
//     std::set<int> closedSet;

//     // Main A* algorithm loop
//     while (!openSet.empty()) {
//         Node current = openSet.top();
//         openSet.pop();

//         if (current.property.latitude == goal.latitude && current.property.longitude == goal.longitude) {
//             // Path found, backtrace to retrieve the path
//             std::vector<Property> path;
//             while (current.parent != nullptr) {
//                 path.push_back(current.property);
//                 current = *current.parent;
//             }
//             path.push_back(start);
//             std::reverse(path.begin(), path.end());
//             return path;
//         }

//         closedSet.insert(current.id);

//         // Iterate over neighbors (properties within proximity for simplicity)
//         for (size_t i = 0; i < properties.size(); ++i) {
//             if (closedSet.count(i)) continue;

//             double tentativeGCost = current.gCost + haversine(current.property.latitude, current.property.longitude, properties[i].latitude, properties[i].longitude);
//             double hCost = haversine(properties[i].latitude, properties[i].longitude, goal.latitude, goal.longitude);
//             Node neighbor = {static_cast<int>(i), tentativeGCost, hCost, properties[i], &allNodes[current.id]};

//             if (!allNodes.count(i) || tentativeGCost < allNodes[i].gCost) {
//                 openSet.push(neighbor);
//                 allNodes[i] = neighbor;
//             }
//         }
//     }

//     // Return empty if no path is found
//     return {};
// }


#include "AStar.h"
#include "Haversine.h"
#include <unordered_map>
#include <set>
#include <cmath>
#include <queue>
#include <algorithm>

std::vector<Property> aStarSearch(double startLat, double startLon, double targetPrice, const std::vector<Property>& properties) {
    // Priority queue to store nodes to explore
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::unordered_map<int, Node> allNodes;  // Map nodes by ID
    std::set<int> closedSet;  // To avoid revisiting nodes

    // Step 1: Find the closest node to the virtual start
    double minDistance = std::numeric_limits<double>::max();
    int closestNodeIndex = -1;

    for (size_t i = 0; i < properties.size(); ++i) {
        double dist = haversine(startLat, startLon, properties[i].latitude, properties[i].longitude);
        if (dist < minDistance) {
            minDistance = dist;
            closestNodeIndex = static_cast<int>(i);
        }
    }

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
        for (size_t i = 0; i < properties.size(); ++i) {
            if (closedSet.count(i)) continue;

            double tentativeGCost = current.gCost + haversine(current.property.latitude, current.property.longitude, properties[i].latitude, properties[i].longitude);
            double hCost = std::abs(properties[i].price - targetPrice) + haversine(properties[i].latitude, properties[i].longitude, startLat, startLon);

            Node neighbor = {static_cast<int>(i), tentativeGCost, hCost, properties[i], &allNodes[current.id]};

            if (!allNodes.count(i) || tentativeGCost < allNodes[i].gCost) {
                openSet.push(neighbor);
                allNodes[i] = neighbor;
            }
        }
    }

    // Step 4: Reconstruct the path
    std::vector<Property> path;
    Node* currentNode = &bestGoalNode;

    while (currentNode != nullptr) {
        path.push_back(currentNode->property);
        currentNode = currentNode->parent;
    }

    // Include the virtual start for completeness
    path.push_back(virtualStart);
    std::reverse(path.begin(), path.end());
    return path;
}
