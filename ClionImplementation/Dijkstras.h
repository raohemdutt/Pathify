#include "Property.h"
#include <vector>
#include "Haversine.h"

struct dNode {
  int id;
  double distance;
  Property property;
  dNode* parent;

};


std::vector<Property> dijkstras(double startLat, double startLon, double targetPrice, const std::vector<Property>& properties);
