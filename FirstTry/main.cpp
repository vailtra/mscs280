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
	vector<int> nums;
	vector<pair<int, edge> > MST;
	ifstream myfile;
	int numVert = 0;

	//Read in file
	myfile.open("C:/Users/Big Pimpin'/source/repos/mscs280-FINALMAYBE/FirstTry/travel.txt");
	if (myfile) {
		int i = 0;
		string data;
		while (getline(myfile, data)) {
			if (numVert != 0) {
				graphFromFile.push_back(data);
			}
			numVert++;
		}
	}

	Graph test(numVert-2);
	string temp = "";

	//I barely even know at this point but it works. insert harold stock image here.
	for (int i = 0; i < graphFromFile.size()-2; i++) {
		//set string to be current line from file
		string my_str = graphFromFile.at(i);

		//Filter out any spaces, [ or ]
		my_str.erase(remove(my_str.begin(), my_str.end(), '['), my_str.end());
		my_str.erase(remove(my_str.begin(), my_str.end(), ' '), my_str.end());
		my_str.erase(remove(my_str.begin(), my_str.end(), ']'), my_str.end());

		//if it's not the last character in the graph
		if ((i != graphFromFile.size() - 1)) {
			//loop through the filtered line's size
			for (int j = 0; j < my_str.size(); j++) {
				//add any characters that are not a comma
				if (my_str.at(j) != ',') {
					//add the characters to the temp string
					temp += my_str.at(j);
				}
				else {
					//convert the temp string to an int
					int num = stoi(temp);
					//add it to the nums vector
					nums.push_back(num);
					//clear the temp string
					temp = "";
					//if it's the last character in my_str
					if (j == my_str.size() - 1) {
						//loop through the nums vector
						for (int x = 0; x < nums.size(); x++) {
							//make sure we don't add duplicate edges
							if ((i<x)) {
								//add edge to graph at pos i, x and the number at the nums vector at x
								cout << "start vertex: " << i << endl;
								cout << "end vertex: " << x << endl;
								cout << "weight : " << nums.at(x) << endl << endl;
								test.addEdge(i, x, nums.at(x));
							}
						}
						//clear the nums array
						nums.clear();
					}
				}
			}
		}
	}

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