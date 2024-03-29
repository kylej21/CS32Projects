# Bruin Tours
This is a project made for UCLA CS32. Bruin Tours is a pathfinding software to route a user around the westwood area to a collection of different "Points of Interest". 

# Overview
This software utilizes a custom HashTable for nearly constant lookup, insertion, and deletion when loading the many MapData points. It utlizes a database-like class called GeoDB to provide easy access to my map data and abstract the HashTable from the user. Finally, I implemented an A* algorithm Route function to generate a sufficient path for the tour.

# How to use
1. Download the source code from this repository.
2. Edit "stops.txt" to have valid a syntactical series of stops. It must follow the format "StopName|Description". The stop name must match one of the stops in MapData.txt, or the software will return no solution.
3. Compile the c++ project. You must compile 4 files - main.cpp, geodb.cpp, router.cpp, & tour_generator.cpp. 
4. Run the executable file produced upon compilation with mapdata.txt and stops.txt listed after.
Example with g++:
g++ -std=c++11 -o main main.cpp geodb.cpp router.cpp tour_generator.cpp
./main mapdata.txt stops.txt

# Software Demo
https://youtu.be/x2o9b22BeC0
