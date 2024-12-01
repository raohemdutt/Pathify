#pragma once
#include "Property.h"
#include <vector>
#include <memory>

// Node structure for A* algorithm
struct Node {
    Property property;
    double g_cost;   // Cost from start to this node
    double h_cost;   // Heuristic cost to target
    double f_cost;   // Total cost (g_cost + h_cost)
    std::shared_ptr<Node> parent;  // Pointer to the parent node in the path

    Node(Property prop, double g, double h, std::shared_ptr<Node> par = nullptr)
        : property(prop), g_cost(g), h_cost(h), f_cost(g + h), parent(par) {}

    // Comparator for priority queue
    bool operator>(const Node &other) const {
        return f_cost > other.f_cost;
    }
};
