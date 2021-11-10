#include <iostream>
#include "travellingsalesman.h"
#include "Graph.h"

/* TRAVELLING SALESMAN PROBLEM
* CHRISTOFIDES ALGORITHM -- USING KRUSKAL'S FOR MINIMUM SPANNING TREE
* 1. FIND MSP
* 2. CREATE A MATCHING FOR THE PROBLEM WITH THE SET OF CITIES OF ODD ORDER.
* 3. FIND EULERIAN TOUR FOR MSP (***DECIDE ON ALGORITHM***)
* 4. CONVERT TO TSP USING SHORTCUTS IF CITY IS VISITED TWICE
*/


int main() {
	vector<pair<int, edge>> MST;
	int weight;

	// Read in file -- contains coordinates of places/cities

	// Declare Graph object.
	//g(# of vertices)
	Graph g(6);

	//addEdge(vertex1, vertex2, weight)
	//test graph
	g.addEdge(0, 1, 5);
	g.addEdge(0, 2, 4);
	g.addEdge(0, 3, 8);
	g.addEdge(1, 2, 12);
	g.addEdge(1, 4, 7);
	g.addEdge(2, 4, 8);
	g.addEdge(2, 5, 2);
	g.addEdge(2, 3, 3);
	g.addEdge(3, 5, 1);
	g.addEdge(4, 5, 4);

	// Construct minimum spanning tree (MST) using Kruskals
	g.kruskal();
	g.print();

	weight = g.getMinimumWeight();
	MST = g.getMST();
	std::cout << weight << std::endl;

	//Returns 0 if there does not exist an edge between the two vertices. The order that you input the vertices in the function does not matter.
	std::cout << g.getWeight(3,5);

	// Find eulerian tour

	// Convert to TSP

	// Print graph/results

	// Ouput to terminal

    return 0;
}