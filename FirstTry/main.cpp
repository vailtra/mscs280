#include <iostream>
#include "Graph.h"
#include "travellingsalesman.h"

/* TRAVELLING SALESMAN PROBLEM
* CHRISTOFIDES ALGORITHM -- USING KRUSKAL'S FOR MINIMUM SPANNING TREE
* 1. FIND MSP (Kruskal's)
* 2. CREATE A MATCHING FOR THE PROBLEM WITH THE SET OF CITIES OF ODD ORDER.
* 3. FIND EULERIAN TOUR FOR MSP
* 4. CONVERT TO TSP USING SHORTCUTS IF CITY IS VISITED TWICE
*/


// Parse string
//struct city {
//	string name;
//	double latitude;
//	double longitude;
//};

// Matrix


int main() {
	vector<pair<int, edge> > MST;

	// Read in file -- contains coordinates of places/cities

	// Declare Graph object.
	//g(# of vertices)
	Graph g(6);

	//addEdge(vertex1, vertex2, weight
	//test graph
	g.addEdge(0, 1, 7);
	g.addEdge(0, 2, 9);
	g.addEdge(0, 3, 99);
	g.addEdge(0, 4, 13);
	g.addEdge(0, 5, 11);

	g.addEdge(1, 2, 16);
	g.addEdge(1, 3, 16);
	g.addEdge(1, 4, 15);
	g.addEdge(1, 5, 99);

	g.addEdge(2, 3, 14);
	g.addEdge(2, 4, 14);
	g.addEdge(2, 5, 99);

	g.addEdge(3, 4, 25);
	g.addEdge(3, 5, 5);

	g.addEdge(4, 5, 99);


	// Construct minimum spanning tree (MST) using Kruskals
	g.kruskal();
	g.print();

	MST = g.getMST();

	std::cout << std::endl << std::endl;
	EulerianTour eulerian(MST, 6);

	eulerian.printMST();

	// Finds odd vertices
	eulerian.findOddVertices();
	eulerian.printOddVertices();

	// Constructs complete graph of odd vertices
	eulerian.inducedSubgraph(g);
	eulerian.printInducedSubgraph();

	// Finds a Perfect Matching of odd vertices
	eulerian.findPerfectMatching();
	eulerian.printPerfectMatching();

	// Overlays Minimum Spanning Tree and Perfect Matching
	eulerian.overlayGraphs();
	eulerian.printOverlay();

	// Hamiltonian Circuit
	eulerian.findHamiltonianCircuit(g);
	eulerian.printHamiltonianCircuit();

	// Print graph/results

	// Ouput to terminal

	return 0;
}

/*
* NOTES:
*	TAKING IN COORDINATES: NEED TO CALCULATE WEIGHTS OF EDGES BETWEEN VERTICES IN ORDER TO FIND INDUCED SUBGRAPH.
*	REQUIRES TO READ COORDINATES INPUTTED BY USER AND STORING INTO A VECTOR
*/