#pragma once
#include "Property.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>
#include "AStar.h"

// Node structure for Dijkstra's algorithm
struct DijkstraNode {
  int id;
  Property property;
  double g_cost;   // Cost from start to this node
  std::shared_ptr<DijkstraNode> parent;  // Pointer to the parent node in the path



  // Default constructor
  DijkstraNode()
      : property(Property{0.0, 0.0, 0.0, ""}), g_cost(0.0), parent(nullptr) {}

  // Constructor
  DijkstraNode(Property prop, double g, std::shared_ptr<DijkstraNode> par = nullptr)
      : property(prop), g_cost(g), parent(par) {}

  // Comparator for priority queue
  bool operator>(const DijkstraNode &other) const {
    return g_cost > other.g_cost;
  }

  // Add a copy assignment operator
  DijkstraNode& operator=(const DijkstraNode& other) {
    if (this != &other) {
      property = other.property;
      g_cost = other.g_cost;
      parent = other.parent;  // Shared pointer assignment
    }
    return *this;
  }

};

// Function declaration for Dijkstra's algorithm
std::tuple<std::vector<Property>, TimingInfo> dijkstraShortestPath(double startLat, double startLon, const std::vector<Property>& properties);
