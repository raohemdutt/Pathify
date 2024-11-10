// AStar.cpp
#include "AStar.h"
#include "Haversine.h"
#include <unordered_map>
#include <set>
#include <cmath>

std::vector<Property> aStarSearch(const Property& start, const Property& goal, const std::vector<Property>& properties) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::unordered_map<int, Node> allNodes;  // Track nodes by ID for efficient access

    // Initialize the start node
    Node startNode = {0, 0.0, haversine(start.latitude, start.longitude, goal.latitude, goal.longitude), start, nullptr};
    openSet.push(startNode);
    allNodes[0] = startNode;

    // A set of closed nodes to avoid revisiting
    std::set<int> closedSet;

    // Main A* algorithm loop
    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.property.latitude == goal.latitude && current.property.longitude == goal.longitude) {
            // Path found, backtrace to retrieve the path
            std::vector<Property> path;
            while (current.parent != nullptr) {
                path.push_back(current.property);
                current = *current.parent;
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet.insert(current.id);

        // Iterate over neighbors (properties within proximity for simplicity)
        for (size_t i = 0; i < properties.size(); ++i) {
            if (closedSet.count(i)) continue;

            double tentativeGCost = current.gCost + haversine(current.property.latitude, current.property.longitude, properties[i].latitude, properties[i].longitude);
            double hCost = haversine(properties[i].latitude, properties[i].longitude, goal.latitude, goal.longitude);
            Node neighbor = {static_cast<int>(i), tentativeGCost, hCost, properties[i], &allNodes[current.id]};

            if (!allNodes.count(i) || tentativeGCost < allNodes[i].gCost) {
                openSet.push(neighbor);
                allNodes[i] = neighbor;
            }
        }
    }

    // Return empty if no path is found
    return {};
}
