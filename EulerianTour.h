#ifndef EULERIANTOUR_H
#define EULERIANTOUR_H
#include <iostream>
#include <fstream>

/* Find Eulerian tour
		* ALL VERTICES OF ODD ORDER MUST BE MADE EVEN -- CREATE VECTOR?
		* COULD CREATE LOOPS -- MUST ENSURE HAMILTONIAN CIRCUIT -- USE SHORTCUTS
		* ALL VERTICES MUST HAVE EVEN ORDER
*/

class EulerianTour {

private:
	std::vector<pair<int, edge>> MST;;
	std::vector<int> oddDegVertices;
	std::vector<int> noDegVertices;
	std::vector<pair<int, edge>> oddVertSubgraph;
	std::vector<pair<int, edge>> perfMatch;
	std::vector<pair<int, edge>> overlay;
	std::vector<pair<int, edge>> tempOverlay;

	int numVertices;

	


public:
	EulerianTour(vector<pair<int, edge>>, int);
	//void printOddVertices();
	void printMST();
	//void findOddVertices();
	//void findHamiltonianCircuit(Graph&);
	void printHamiltonianCircuit();
	int findMinimumWeight();
	int findMaximumWeight(Graph&, int);
	void printToFile();
	void printOverlay();
	void hamilton(std::vector <int> preTran, Graph& weight);
};

EulerianTour::EulerianTour(vector<pair<int, edge>> MST, int numVertices) {
	this->MST = MST;
	this->numVertices = numVertices;
	this->overlay = MST;
}

//void EulerianTour::findOddVertices() {
//	int counter;
//	int i;
//
//	// Counts number of odd vertices in graph
//	for (int currVert = 0; currVert < numVertices; ++currVert) {
//
//		counter = 0;
//		for (i = 0; i < MST.size(); ++i) {
//			if (MST[i].second.first == currVert) {
//				++counter;
//			}
//			if (MST[i].second.second == currVert) {
//				++counter;
//			}
//		}
//
//		if (counter % 2 != 0) {
//			oddDegVertices.push_back(currVert);
//		}
//	}
//}
//
//void EulerianTour::printOddVertices() {
//	std::cout << std::endl << std::endl << "Odd vertices: ";
//	for (int i = 0; i < oddDegVertices.size(); i++) {
//		std::cout << oddDegVertices.at(i) << " ";
//	}
//}


void EulerianTour::printMST() {
	std::cout << std::endl << std::endl << "Minimum Spanning Tree: " << std::endl;
	for (int i = 0; i < MST.size(); i++) {
		std::cout << MST[i].second.first << " - " << MST[i].second.second << " : "
			<< MST[i].first;
		std::cout << std::endl;
	}
}

//void EulerianTour::findHamiltonianCircuit(Graph& weight) {
//	int numDeg;
//	int index;
//	int count;
//	vector<int> indexDoubleVert;
//	// Vertice, and its degree
//	std::vector<pair<int, int>> tooManyVert;
//	// finds the vertices with degree > 2
//	for (int i = 0; i < numVertices; ++i) {
//		numDeg = 0;
//		for (int j = 0; j < overlay.size(); ++j) {
//			if (i == overlay.at(j).second.first) {
//				++numDeg;
//			}
//			if (i == overlay.at(j).second.second) {
//				++numDeg;
//			}
//		}
//		if (numDeg > 2) {
//			tooManyVert.push_back(make_pair(i, numDeg));
//		}
//	}
//
//	// Deletes edges from vertices with degree > 2
//	for (int i = 0; i < tooManyVert.size(); ++i) {
//		numDeg = tooManyVert.at(i).second;
//	//	std::cout << tooManyVert.at(i).first << " " << numDeg;
//		while (numDeg > 2) {
//			
//			index = this->findMaximumWeight(weight, tooManyVert.at(i).first);
//			overlay.erase(overlay.begin() + index);
//			numDeg--;
//			
//		}
//		std::cout << std::endl;
//	}
//
//	int counter;
//	int k;
//	oddDegVertices.clear();
//
//	// Counts number of odd vertices now in overlay
//	for (int currVert = 0; currVert < numVertices; ++currVert) {
//
//		counter = 0;
//		for (k = 0; k < overlay.size(); ++k) {
//			if (overlay[k].second.first == currVert) {
//				++counter;
//			}
//			if (overlay[k].second.second == currVert) {
//				++counter;
//			}
//		}
//
//		if (counter % 2 != 0) {
//			oddDegVertices.push_back(currVert);
//			//std::cout << "CurrVert: " << currVert << std::endl;
//		}
//	}
//
//	// Counts no degree vertices
//	for (int currVert = 0; currVert < numVertices; ++currVert) {
//
//		counter = 0;
//		for (k = 0; k < overlay.size(); ++k) {
//			if (overlay[k].second.first == currVert) {
//				++counter;
//			}
//			if (overlay[k].second.second == currVert) {
//				++counter;
//			}
//		}
//
//		if (counter == 0) {
//			noDegVertices.push_back(currVert);
//			std::cout << "CurrVert: " << currVert << std::endl;
//		}
//	}
//
//	counter = 0;
//	k = noDegVertices.size() - 1;
//
//	// Attached no deg vertices to odd vertices
//	while (!noDegVertices.empty()) {
//		
//		
//		for (int i = 0; i < oddDegVertices.size(); ++i) {
//			k = noDegVertices.size() - 1;
//			if (noDegVertices.empty()) {
//				break;
//			}
//			if (counter > oddDegVertices.size() - 1) {
//				break;
//			}
//
//			overlay.push_back(make_pair(weight.getWeight(oddDegVertices.at(i),
//				noDegVertices.at(k)), edge(oddDegVertices.at(i),
//					noDegVertices.at(k))));
//			noDegVertices.erase(noDegVertices.begin() + k);
//			counter++;
//			
//		}
//		if (counter > oddDegVertices.size() - 1) {
//			break;
//		}
//	}
//
//	// Attached remaining no deg vert to no deg vert
//	while (!noDegVertices.empty()) {
//		overlay.push_back(make_pair(weight.getWeight(noDegVertices.at(0),
//			noDegVertices.at(1)), edge(noDegVertices.at(0),
//				noDegVertices.at(1))));
//		this->printOverlay();
//		noDegVertices.erase(noDegVertices.begin());
//		noDegVertices.erase(noDegVertices.begin());
//	}
//
//	for (int currVert = 0; currVert < numVertices; ++currVert) {
//
//		counter = 0;
//		for (k = 0; k < overlay.size(); ++k) {
//			if (overlay[k].second.first == currVert) {
//				++counter;
//			}
//			if (overlay[k].second.second == currVert) {
//				++counter;
//			}
//		}
//
//		if (counter % 2 != 0) {
//			oddDegVertices.push_back(currVert);
//			std::cout << "CurrVert: " << currVert << std::endl;
//		}
//	}
//	
//	int prevConVert = -1;
//	while (!oddDegVertices.empty()) {
//		count = 1;
//		index = oddDegVertices.size() - 1;
//		for (int i = 0; i < overlay.size(); ++i) {
//			if ((oddDegVertices.at(index - count) == overlay.at(i).second.first && oddDegVertices.at(index) == overlay.at(i).second.second)
//				|| (oddDegVertices.at(index) == overlay.at(i).second.first && oddDegVertices.at(index - count) == overlay.at(i).second.second)) {
//
//				count++;
//				i = 0;
//			}
//			if (oddDegVertices.size() > 2) {
//				if (prevConVert == overlay.at(i).second.first
//					|| prevConVert == overlay.at(i).second.second) {
//					count++;
//					i = 0;
//				}
//			}
//		}
//
//		for (int i = 0; i < overlay.size(); i++) {
//			if (oddDegVertices.at(index - count) == overlay.at(i).second.first) {
//				prevConVert = overlay.at(i).second.second;
//			}
//			else if (oddDegVertices.at(index - count) == overlay.at(i).second.second) {
//				prevConVert = overlay.at(i).second.first;
//			}
//		}
//		
//		overlay.push_back(make_pair(weight.getWeight(oddDegVertices.at(index - count), oddDegVertices.at(index)), edge(oddDegVertices.at(index - count), oddDegVertices.at(index))));
//		std::cout << "Odd deg vert -- " << oddDegVertices.at(index - count) << " : " << oddDegVertices.at(index) << std::endl;
//		
//		oddDegVertices.erase(oddDegVertices.begin() + index);
//		oddDegVertices.erase(oddDegVertices.begin() + index - count);
//	
//	}
//	
//	/*for (int i = 1; i < oddDegVertices.size(); i += 2) {
//		overlay.push_back(make_pair(weight.getWeight(oddDegVertices.at(i - 1), oddDegVertices.at(i)), edge(oddDegVertices.at(i - 1), oddDegVertices.at(i))));
//	}*/
//
//}

void EulerianTour::printHamiltonianCircuit() {
	std::cout << std::endl << std::endl << "Hamiltonian Circuit: "
		<< std::endl;
	for (int i = 0; i < overlay.size(); i++) {
		std::cout << overlay[i].second.first << " - " << overlay[i].second.second << " : "
			<< overlay[i].first;
		std::cout << std::endl;
	}
}

// Returns the index of the minimun weight
int EulerianTour::findMinimumWeight() {
	// Set the minimum value of the weight to be the fist vertex in the graph aswell as index to be set to 0
	int min = oddVertSubgraph[0].first;
	int index = 0;
	// loop through the oddVertSubgraph
	for (int i = 0; i < oddVertSubgraph.size(); i++) {
		// Check to see if the weight at the current index i is less than the previous minimum
		if (oddVertSubgraph[i].first < min) {
			// Set the new minimum to be the value of the weight at this index i
			min = oddVertSubgraph[i].first;
			// Set the index variable equal to i (the location that the minimum weight is at in the oddVertSubgraph)
			index = i;
		}
	}
	// Return the index that the minimum weight exists at
	return index;
}

// Returns the index of the maximum weight
int EulerianTour::findMaximumWeight(Graph& weight, int vert) {
	int max = 0;
	int index = 0;
	for (int i = 0; i < overlay.size(); ++i) {
		if (vert == overlay.at(i).second.first && overlay.at(i).first > max) {
			max = overlay.at(i).first;
			index = i;
		}
		if (vert == overlay.at(i).second.second && overlay.at(i).first > max) {
			max = overlay.at(i).first;
			index = i;
		}
	}
	return index;
}

void EulerianTour::printToFile() {
	std::ofstream file;
	file.open("graph.txt");

	for (int i = 0; i < MST.size(); i++) {
		file << MST[i].second.first << " " << MST[i].second.second << " "
			<< MST[i].first;
		file << std::endl;
	}

	file.close();
}

void EulerianTour::printOverlay() {
	std::cout << std::endl << std::endl << "Overlay of Perfect Matching and Minimum Spanning Tree: "
		<< std::endl;
	for (int i = 0; i < overlay.size(); i++) {
		std::cout << overlay[i].second.first << " - " << overlay[i].second.second << " : "
			<< overlay[i].first;
		std::cout << std::endl;
	}
}

void EulerianTour::hamilton(std::vector <int> preTran, Graph& weight) {
	overlay.clear();
	for (int i = 1; i < preTran.size(); ++i) {
		overlay.push_back(make_pair(weight.getWeight(preTran.at(i), preTran.at(i-1)), edge(preTran.at(i), preTran.at(i-1))));
		
	}
	int size = preTran.size();
	overlay.push_back(make_pair(weight.getWeight(preTran.at(0), preTran.at(size - 1)), edge(preTran.at(0), preTran.at(size - 1))));

	std::ofstream file1;
	file1.open("graph1.txt");
	for (int i = 0; i < overlay.size(); i++) {
		file1 << overlay[i].second.first << " " << overlay[i].second.second << " "
			<< overlay[i].first;
		file1 << std::endl;
	}

	file1.close();

}



#endif

