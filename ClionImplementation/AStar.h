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

struct TimingInfo {
    long long step1Time;
    long long step2Time;
    long long step3Time;
    long long step4Time;
    long long totalTime;
};


// Function to perform A* search and return the shortest path
std::tuple<std::vector<Property>, TimingInfo> aStarSearch(double startLat, double startLon, double targetPrice, const std::vector<Property>& properties);
