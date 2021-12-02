#include <iostream>
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include "travellingsalesman.h"
using namespace std;

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
	vector<string> graphFromFile;
	vector<string> parsed;
	ifstream myfile;
	myfile.open("C:/Users/Big Pimpin'/source/repos/mscs280-FINALMAYBE/FirstTry/travel.txt");

	if (myfile) {
		int i = 0;
		string data;
		while (getline(myfile, data)) {
			graphFromFile.push_back(data);
			i++;
		}
	}
	
	string delimiter = "[";
	for (int i = 1; i < graphFromFile.size(); i++) {
		//string token = graphFromFile.at(i).substr(0, graphFromFile.find(",");
		if ((i != graphFromFile.size() - 1)) {
			cout << graphFromFile.at(i) << endl;
		}
	}


	vector<pair<int, edge> > MST;

	// Read in file -- contains coordinates of places/cities

	int numVert = 3;
	Graph test(numVert);
	// ADD EDGES
	test.addEdge(0, 1, 2);
	test.addEdge(0, 2, 2);
	test.addEdge(1, 2, 1);

	// CONSTRUCT MINIMUM SPANNING TREE
	test.kruskal();
	MST = test.getMST();

	EulerianTour eulerian(MST, numVert);

	eulerian.printMST();

	// FINDS ODD VERTICES
	eulerian.findOddVertices();
	eulerian.printOddVertices();

	// COMPLETE GRAPH INDUCED BY ODD VERTICES
	eulerian.inducedSubgraph(test);
	eulerian.printInducedSubgraph();

	// PERFECT MATCHING OF ODD VERTICE INDUCED SUBGRAPH
	eulerian.findPerfectMatching();
	eulerian.printPerfectMatching();

	// OVERALY OF MINIMUM SPANNING TREE AND PERFECT MATCHING
	eulerian.overlayGraphs();
	eulerian.printOverlay();

	// CONSTRUCTS HAMILTON CIRCUIT
	eulerian.findHamiltonianCircuit(test);
	eulerian.printHamiltonianCircuit();

	// Ouput to terminal

	return 0;
}

/*
* NOTES:
*	TAKING IN COORDINATES: NEED TO CALCULATE WEIGHTS OF EDGES BETWEEN VERTICES IN ORDER TO FIND INDUCED SUBGRAPH.
*	REQUIRES TO READ COORDINATES INPUTTED BY USER AND STORING INTO A VECTOR
*/