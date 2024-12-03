// AStar.h
#pragma once
#include <vector>
#include <queue>
#include "Property.h"

struct Node {
    int id;
    double gCost;  // Cost from start node to this node
    double hCost;  // Estimated cost from this node to end node (heuristic)
    double fCost() const { return gCost + hCost; }
    Property property;
    Node* parent;

    bool operator>(const Node& other) const { return fCost() > other.fCost(); }
};

// Function to perform A* search and return the shortest path
std::vector<Property> aStarSearch(double startLat, double startLon, double targetPrice, const std::vector<Property>& properties);
