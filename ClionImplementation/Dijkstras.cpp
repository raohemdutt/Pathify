
#include <map>
#include <set>
#include <queue>
#include "Dijkstras.h"
#include <limits>
#include <cmath>

std::vector<Property> dijkstras(double startLat, double startLon, double targetPrice, const std::vector<Property>& properties) {
  std::vector<Property> finalPath;
  //Find destination point so we can find shortest distance to it
  std::vector<dNode> allNodes;
  double minPrice = 999999999999999999;
  //Add Starting Node to Node list
  dNode minNode;
  minNode.id = 0;
  minNode.property.latitude = startLat;
  minNode.property.longitude = startLon;
  minNode.property.price = targetPrice;
  allNodes.push_back(minNode);

  //Then loop and add the nodes
  for (int i = 0; i < properties.size(); i++) {
    dNode newNode;
    newNode.id = i+1;
    //Distance physically plus the distance financially
    newNode.distance = haversine(startLat,startLon,properties[i].latitude, properties[i].longitude);
    newNode.property = properties[i];
    allNodes.push_back(newNode);
    if(newNode.property.price < minPrice) {
      minPrice = newNode.property.price;
      minNode = newNode;
    }
  }
  //Add starting Node to Final Path
  finalPath.push_back(minNode.property);

  //Create Adjacency List with the int/id corresponding to the from id and the other pair having the to id and the Node
  std::map<int, std::vector<std::pair<int, double> > > adjacencyList;
  for(int i = 0; i < allNodes.size(); i++) {
    for(int j = 0; j < allNodes.size(); j++) {
      std::pair<int, double> pairs;
      if(i != j) {
        //make a pair with the node id and the distance
        pairs = std::make_pair(j, haversine(allNodes[i].property.latitude, allNodes[i].property.longitude,allNodes[j].property.latitude, allNodes[j].property.longitude));
      }

      adjacencyList[i].push_back(pairs);
    }
    std::cout<<"outer"<<std::endl;
  }

  //We constructed a large map
//Now Run Dijkstra



  return finalPath;
}