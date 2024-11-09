# Pathify
DSA Project 3, Team 27

Project 3A

Team Name:
Pathfinders


Team Members:
Kai McFarlane, Joshua Brunk, Hemdutt Rao


Project Title: 
Pathify

Problem: What problem are we trying to solve? [0.25 point]
We aim to provide users in Saudi Arabia with accurate, location-based property price insights by leveraging various algorithms. The goal is to compare two algorithms—Dijkstra’s and A*—for finding the shortest path in a city road network, simulating real-world navigation problems. This project will focus on how well each algorithm performs in terms of speed and efficiency on a large dataset. 

Motivation: Why is this a problem [0.25 point]
As real-time navigation services grow in demand, the efficiency of shortest-path algorithms is becoming increasingly critical. While applications like Google Maps and other routing services rely on fast, reliable algorithms to compute optimal routes, the niche of integrating property prices relative to location remains largely underexplored. To enhance such systems, it's essential to understand the strengths and limitations of commonly used algorithms, such as Dijkstra's and A*, and how they can be optimized for this specific use case.

Features: When do we know that we have solved the problem? [0.25 point]
We will know the problem is solved when:
The user can filter properties by price or area.
The system finds a set of nodes ( real-estate properties) matching the filter, then runs Dijkstra’s and A* algorithms to find the shortest path.
Min-heap-based priority queue will be used for node management during traversal
The frontend will display the map with the resulting nodes, the output includes a clear path representation
The solution includes a comparison of the two algorithms (Dijkstra and A*) in terms of speed, efficiency, and memory usage.

Data: (Public data set we will be using and the link to the public data set) or (Schema of randomly generated data - i.e. what are the different columns in our dataset and the 
respective datatypes) [0.25 point]

We will use the Saudi Arabia real estate dataset available on Kaggle:
https://www.kaggle.com/datasets/evgeniionegin/saudi-arabia-real-estate-dataset?select=merged_data.csv
	
Tools: Programming languages or any tools/frameworks we will be using [0.25 point]

React: Frontend interface
Python: Backend development and data processing
C++: Algorithm implementation (Dijkstra and A*)
Crow: C++ framework for creating a Websocket 
	
Visuals: Sketches of the interface or the menu driven program [0.25 points] 
The interface will feature a menu-driven system where users can filter properties by price and area. The output will display a map with selected nodes and paths, representing the shortest path using two algorithms. For a detailed sketch, please refer to Appendix A. 
	
Strategy: Preliminary algorithms or data structures you may want to implement and how would you represent the data [0.25 points]
Dijkstra’s Algorithm will be used for efficient pathfinding without incorporating any heuristics.
A* Algorithm will use heuristics for faster pathfinding results.
Both Dijkstra’s and A* will rely on a priority queue to manage nodes during graph traversal, ensuring that the node with the lowest cost is processed first in Dijkstra’s case, and the node with the shortest estimated total distance is prioritized in A*.
The priority queue will be implemented using a min-heap for efficient insertion and extraction of nodes in logarithmic time (O(log n)).

Distribution of Responsibility and Roles: Who is responsible for what? [0.25 points]
Joshua - Dijkstra’s Algorithm implementation and API integration
Kai - Frontend development (implementing user interface for choosing location and price, and calling requests to backend server for information)
Hemdutt - A* algorithm design and implementation



References 

https://www.kaggle.com/datasets/evgeniionegin/saudi-arabia-real-estate-dataset?select=merged_data.csv
https://www.baeldung.com/cs/dijkstra-vs-a-pathfinding

