#ifndef TRAVELLINGSALESMAN_H
#define TRAVELLINGSALESMAN_H

/* Find Eulerian tour
		* ALL VERTICES OF ODD ORDER MUST BE MADE EVEN -- CREATE VECTOR?
		* COULD CREATE LOOPS -- MUST ENSURE HAMILTONIAN CIRCUIT -- USE SHORTCUTS
		* ALL VERTICES MUST HAVE EVEN ORDER
*/

class EulerianTour {

private:
	std::vector<pair<int, edge>> MST;;
	std::vector<int> oddDegVertices;
	std::vector<pair<int, edge>> oddVertSubgraph;
	std::vector<pair<int, edge>> perfMatch;
	std::vector<pair<int, edge>> overlay;

	int numVertices;




public:
	EulerianTour(vector<pair<int, edge>>, int);
	void inducedSubgraph(Graph&);
	void printInducedSubgraph();
	void printOddVertices();
	void printMST();
	void printPerfectMatching();
	void findPerfectMatching();
	void findOddVertices();
	void overlayGraphs();
	void printOverlay();
	void findHamiltonianCircuit(Graph&);
	void printHamiltonianCircuit();
	int findMinimumWeight();
};

EulerianTour::EulerianTour(vector<pair<int, edge>> MST, int numVertices) {
	this->MST = MST;
	this->numVertices = numVertices;
}

void EulerianTour::findOddVertices() {
	int counter;
	int i;

	// Counts number of odd vertices in graph
	for (int currVert = 0; currVert < numVertices; ++currVert) {

		counter = 0;
		for (i = 0; i < MST.size(); ++i) {
			if (MST[i].second.first == currVert) {
				++counter;
			}
			if (MST[i].second.second == currVert) {
				++counter;
			}
		}

		if (counter % 2 != 0) {
			oddDegVertices.push_back(currVert);
		}
	}
}

void EulerianTour::printOddVertices() {
	std::cout << std::endl << std::endl << "Odd vertices: ";
	for (int i = 0; i < oddDegVertices.size(); i++) {
		std::cout << oddDegVertices.at(i) << " ";
	}
}

void EulerianTour::inducedSubgraph(Graph& weight) {

	// Creates complete subgraph of odd vertices
	for (int i = 0; i < oddDegVertices.size(); ++i) {
		for (int j = 0; j < oddDegVertices.size(); ++j) {
			if (i > j) {
				oddVertSubgraph.push_back(make_pair(weight.getWeight(oddDegVertices.at(i), oddDegVertices.at(j)), edge(oddDegVertices.at(i), oddDegVertices.at(j))));
			}
		}
	}
}

void EulerianTour::printInducedSubgraph() {
	std::cout << std::endl << std::endl << "Induced subgraph of odd vertices: " << std::endl;
	for (int i = 0; i < oddVertSubgraph.size(); ++i) {
		std::cout << oddVertSubgraph[i].second.first << " - " << oddVertSubgraph[i].second.second << " : "
			<< oddVertSubgraph[i].first;
		std::cout << std::endl;
	}
}


// LIMITATIONS OF CHRISTOFIDES: MINIMUM PERFECT MATCHING NEEDED
// Finding minimum WEIGHT perfect matching is difficult, need help
void EulerianTour::findPerfectMatching() {

	// first & second vertices
	int x, y;
	// i = perfMatch size iterator and j = oddVertSubgraph size iterator
	int i, j;
	// Size of perfMatch
	int currSize = 0;

	// Takes first edge in oddVertSubgraph and uses it as starting edge for perfect matching in new graph
	perfMatch.push_back(oddVertSubgraph.at(findMinimumWeight()));

	// While oddVert is not empty
	while (oddVertSubgraph.size() > 0) {

		i = perfMatch.size() - 1; // iterator
		x = perfMatch.at(i).second.first; // end vertices of current edge
		y = perfMatch.at(i).second.second;
		j = oddVertSubgraph.size() - 1; // iterator

		// Not empty and iterator is not below 0
		while (j >= 0 && oddVertSubgraph.size() > 0) {

			// Checks if x and y exists in the odd vertice complete graph and removes 
			// all edges that contain those vertices
			if (x == oddVertSubgraph.at(j).second.first || x == oddVertSubgraph.at(j).second.second
				|| y == oddVertSubgraph.at(j).second.first || y == oddVertSubgraph.at(j).second.second) {
				oddVertSubgraph.erase(oddVertSubgraph.begin() + j);
				--i;
			}
			--j;
		}

		// If i is still equivalent to the perfMatch size, then all x and y vertices have 
		// been removed oddVertSubgraph and can push the next edge into perfMatch
		if (i == perfMatch.size() - 1)
		{
			perfMatch.push_back(oddVertSubgraph.at(0));
		}
	}
}

void EulerianTour::printPerfectMatching() {
	std::cout << std::endl << std::endl << "Perfect Matching: " << std::endl;
	for (int i = 0; i < perfMatch.size(); ++i) {
		std::cout << perfMatch[i].second.first << " - " << perfMatch[i].second.second << " : "
			<< perfMatch[i].first;
		std::cout << std::endl;
	}
}

void EulerianTour::printMST() {
	std::cout << std::endl << std::endl << "Minimum Spanning Tree: " << std::endl;
	for (int i = 0; i < MST.size(); i++) {
		std::cout << MST[i].second.first << " - " << MST[i].second.second << " : "
			<< MST[i].first;
		std::cout << std::endl;
	}
}

void EulerianTour::overlayGraphs() {
	overlay = perfMatch;
	overlay.insert(overlay.end(), MST.begin(), MST.end());
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

void EulerianTour::findHamiltonianCircuit(Graph& weight) {
	int numDeg;
	// Vertice, and its degree
	std::vector<pair<int, int>> tooManyVert;

	// finds the vertices with degree > 2
	for (int i = 0; i < numVertices; ++i) {
		numDeg = 0;
		for (int j = 0; j < overlay.size(); ++j) {
			if (i == overlay.at(j).second.first) {
				++numDeg;
			}
			if (i == overlay.at(j).second.second) {
				++numDeg;
			}
		}
		if (numDeg > 2) {
			tooManyVert.push_back(make_pair(i, numDeg));
		}
	}

	// Deletes edges from vertices with degree > 2
	for (int i = 0; i < tooManyVert.size(); ++i) {
		numDeg = tooManyVert.at(i).second;
		for (int j = 0; j < overlay.size(); ++j) {
			if (tooManyVert.at(i).first == overlay.at(j).second.first && numDeg > 2) {
				overlay.erase(overlay.begin() + j);
				--numDeg;
			}
			if (tooManyVert.at(i).first == overlay.at(j).second.second && numDeg > 2) {
				overlay.erase(overlay.begin() + j);
				--numDeg;
			}
		}
	}

	int counter;
	int k;
	oddDegVertices.clear();

	// Counts number of odd vertices now in overlay
	for (int currVert = 0; currVert < numVertices; ++currVert) {

		counter = 0;
		for (k = 0; k < overlay.size(); ++k) {
			if (overlay[k].second.first == currVert) {
				++counter;
			}
			if (overlay[k].second.second == currVert) {
				++counter;
			}
		}

		if (counter % 2 != 0) {
			oddDegVertices.push_back(currVert);
		}
	}

	// Connects odd vertices
	for (int i = 1; i < oddDegVertices.size(); i += 2) {
		overlay.push_back(make_pair(weight.getWeight(oddDegVertices.at(i - 1), oddDegVertices.at(i)), edge(oddDegVertices.at(i - 1), oddDegVertices.at(i))));
	}
}

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


#endif
