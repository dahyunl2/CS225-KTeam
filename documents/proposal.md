## Leading Question 
Our goal is to determine the shortest flight time and distance using the “OpenFlights” dataset.
Our first question is to find the routes to destination with minimum transits. 
We will use BFS traversal to find the shortest routes between the airports with a given departing location and arriving location based on the least amount of connecting flights. 

Second question is to find the best route among routes with the same transits.
We will use Dijkstra’s algorithm to calculate the shortest path between the two airports based on the shortest distance traveled. 

Third question is to find the best airport with layovers. 
Using the same logic, our group is planning to implement a layover function to find the shortest distance between departing airport and arriving airport with one or more layovers. 
 

## Dataset Acquisition
Source - Openflights: https://openflights.org/data.html 

## Data Format
We will be using airports as vertices, and use flight between airports as edges.For airport data, there are over 10,000 transportation facilities include train station, ports, airports etc… Since we only need data for airports, we will use airport.dat which contains only airports. The data is UTF-8 encoded with variables separated with commas. For route data, we will use routes.dat that includes 67663 routes between 3321 airports on 548 airlines spanning the globe. The data is also  UTF-8 encoded with variables separated with commas.

## Data Correction
 We will parse from the OpenFlights/Airline Route Mapper Route Database in order to extract the data we only need. Each vertices will certainly include “airline ID”, “latitude” , “longitude”, and potentially include “city”, ”country” etc….Each edges will include “airline ID”, “source airport ID”, “destination airport ID”, and “stops”. 

## Data Storage
 We will be using airports as vertices, and use flight between airports as edges. These data sets will be used with CSV files read using offstream or ifstream for finding the shortest distance. We will be using 2 dimensions to derive the results on a map. We will find the shortest path from one vertex to all other vertices with minimized error. The estimated spacial complexity for data storage is O(V*E).

## Algorithm 
 The input for the program will be the starting airport and destination airport, and the output will be the shortest connecting flight between two points and its total distance. We are expected to create a graph whose vertices are all the airports in the dataset to use the following graph algorithms. We will be printing out the connecting flight as IATA, which is 3-letter IATA code.
For BFS, we will first make an adjacency list for the airport graph for the memory efficiency. This will take O(V+E) where V is the number of vertices and E is the number of edges because we have to search all adjacency lists of the head node to each vertex. Then, to find the edge connecting two airports, we should search for the adjacency list of vertices, which will take O(V).
For Dijkstra’s Algorithm, we will be using longitude and latitude of airports to set the weight of edges between airports. Since insertion function for the Dijkstra algorithm requires to insert all edges, it will take about O(E*log(E)) time. Extracting each node from the priority queue will take about O(V*log(V)) time because it there will be V nodes, and because this should be calculated for all nodes and edges, it will take total of O((V+E)*log(V)) runtime. 
Page Rank algorithm will be used to measure and visualize the important airports from the given dataset. There will be two inputs for this algorithm; First, a node of the airport graph we previously created, and second, the range of the airport we want our adjacency matrix to include. From the adjacency matrix we created, we can use built in library to find the eigenvalue of the adjacency matrix.
Time Complexity will be O(E⋅k) where E is the number of edges and k is the number of iterations. With the given range of airports, the algorithm calculates the relative importance of distances between airports. 

## Timeline
### Week 1 (Nov 1- Nov 6)
Nov 4:      
Submit Team Contract and Project proposal.
Complete initial repository.
 
### Week 2 (Nov 7 - Nov 13)
Nov 6-7:  
Make sure everyone sets up properly. Complete Makefile.
 
Nov 8-9:  
Complete code structure outline.
Complete converting data to proper array format.
 
Nov 10-11:
Complete converting data to proper array format.& Complete array data to graph format.
 
Nov 11-12:
Starting BFS traversals(BFS.h).
 
### Week 3 (Nov 14 - Nov 20):
Nov 14-18:
Mid-Project Check In.(Meet with mentor)
 
Nov 13-15:  
Complete BFS traversals.
 
Nov 16-20: 
Starting Dijkstra’s algorithim
 
### Week 4 (Nov 21 - Dec 27):
Nov 21-23:
Complete Dijkstra’s and verification test.
 
Nov 23-27
Perfect the project and test program effectiveness.
 
### Week 5 (Nov 28 – Dec 4)
Nov 28-30:
Complete presentation.
Complete descriptive README.
Complete written report.
 
Dec 1-4:
Complete the project (functional code check).
 
### Week 6 (Dec 5 – Dec 9)
Dec 8:
Final Presentation
