#Flight.cpp
In the Flight.cpp file, we created a Flight class whose object will have the ids of the departure and destination airports and the distance between those airports, and this distance member will be used to calculate the weight of the node later in the graph function. We also have getters, setters, and the overloaded equality operator to check if two edges are the same and the comparison operator to compare the distance between edges.


#Airport.cpp
In the Airport.cpp file, we’ve been working on parsing the airport dataset so that we can create an Airport object which will be a vertex of a graph. The airport object will have its id, name, city, country, latitude, and longitude as its private members, so we made a constructor with each line of the dataset as its parameter, stored each data in a vector, and assigned corresponding data to members. We had several helper functions that could slice each line with a given separator and trim whitespaces on the left and right sides of the string. We also made getter functions for each member. 
We had two test cases to check if Airport constructors were working correctly, each with the vector of string and string as a parameter. We confirmed that constructors were creating a desired output, so we moved on to creating a graph for the dataset.

#graph.cpp
The key function of the graph.cpp file is to parse given airports and routes data to populate airportMap (adjacency matrix). Airport Map has a key of each airport’s ID and value of Airport Class that is implemented in a separate file. This class also populates a map (destAps) that stores flight information of each airport. These destAps function as weighted edges in our graph. In order to weight the edges, we implemented calcWeight that receives two airport ids and calculates the weight between the two airports by comparing their latitude and longitude. 

To test our Graph class, we construct a graph with the actual airport and route data. Among thousands of airports, we’ve picked Incheon International for testing purposes. To test if our graph class has successfully populated airport data, we used an iterator to traverse the whole map and find Incheon airport. Then, we iterate through all key-value pairs in the destination map inside Incheon airport instance. The value part of the pair is Flight instance which has source airport ID and destination ID. We expect its source airport to be Incheon airport. 

#djikstras.cpp
For Djikstra’s algorithm, we have a constructor which operates the process of finding the shortest path between airports and storing that path to the member variable named path, which will later be returned by getMinDist. The input of the constructor will be the graph of connected airports and the name of starting and destination airports. We had two helper functions, mapInitialize and findpaths; The function mapInitialize initializes three maps, distances(distances between airports), isvisited(boolean map which shows if each airports are visited), prevNodes(previous nodes). The function findpaths finds the paths between airports and updates the distances with the shortest path.

Then, we have getNeighbor function which finds all of the neighbors (adjacent) airports of the root airport. Its input will be a root; the name of an airport that we want to know the neighbors, and will return a vector of pairs<neighboring airport, the distance from this airport to the root>. There are also getters for the shortest path between two airports and vertices that include all airports in the path. Finally, hasVertex function checks if the airport(node) is included in the neighbor_list (the list of the adjacent airport). Its input is the name of the airport that we want to know if it is in the neighbor_list, and returns a boolean which indicates if the neighbor_list has node or not.

The test case for Dijkstra's algorithm checks the shortest path between Charles de Gaulle International Airport to Vancouver International Airport, and the visited airports in the shortest path are shown below.

#Page Rank.cpp/ Page Rank.h
The key function of PageRank class is to create a vector of doubles (pr_output) which indicates the importance of each airport. There is a name_list member variable in our PageRank class that corresponds to our final output. We created this helper member variable to easily obtain the name of the airport with the index. To create an initial random vector, we need the number of dimensions (number of airports in the given data). There is a dim member variable for this reason. Before performing the actual ranking algorithm, we have to prepare an adjacency matrix with the given damping factor. We have implemented the make_adj() function that adjusts our matrix by the damping factor. rank() function is the actual calculation which is basically a dot product. rank() function produces a vector of doubles with the full number of dimensions. To obtain the top most important airports we implemented the top_N_airport function. 

We have 2 test cases for Page rank algorithms. For the first case, have manually created our final pr_output and name_list to test top_N_airport. Since the element with index of 1 has the largest value, we know that our top_N_airport function is working correctly. For the second case, we are constructing a graph from a subset of data and executing a page rank algorithm. As mentioned above, to test the Page rank algorithm, first we need to create a new PageRank instance. Then, we put the instance inside graph.adjMatrix() function as a parameter. This will populate an adjacency matrix in the Page rank instance with airport and edge data. Then we execute make_adj() with a damping factor of 0.85. Then we executed rank() with 150 iterations to create our final page_rank_output. Lastly we executed top_N_airports() to obtain the top most important airports.

#Test.cpp
We made 5 types of test cases to confirm our code is working properly. All of them have passed properly:
1)Testing Airport Constructor: vector<string> input
2)Testing Airport Constructor: string input
3)Testing Graph constructor
4)Testing Pagerank function top_airport()
5)Testing Pagerank implementation on a subset of the whole data set
 
#Answer to the leading questions
Leading Questions:
1)Find the routes to destination with minimum transits.
2)Find the best route among routes with the same transits.
3)Find the best airport with layovers.
Our goals were to determine the shortest flight time and distance using the “OpenFlights” dataset, and we successfully accomplished this using BFS and Dijkstra’s Algorithms. 
We answered the question 1 by using BFS algorithm and we succesfully return the shortest path in terms of minimum transit. 
We answered the second question by using Dijkstra and we successfully return the shortest distance of the possible path. 
We answered the third question by using PageRank so that we found the most important airport (which has greatest number of layovers at that airport)