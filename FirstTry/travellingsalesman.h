#ifndef TRAVELLINGSALESMAN_H
#define TRAVELLINGSALESMAN_H

#include <vector>

class TSP {
private:
	// Coordinates x, y
	double x; // could do doubles if we want
	double y;

	// Number of cities -- Cardinality
	int numCities;

	// Vector to hold coordinates -- could use struct for coordinates then store into vector
	struct coordXY {
		int x;
		int y;
	};

	std::vector <coordXY> coordinates;

	// Length of MSP
	int length;


public:

	// Constuctor
	TSP() {}
	// Destructor
	~TSP() {}
	// Copy constructor
	
	// Find MSP -- why kruskal? FAMILIARITY
	std::vector<coordXY> kruskal(/*G, v*/) {
		/*
		* look on page 56 for kruskal's algorithm	
		*/
	}

	/* Find Eulerian tour
		* ALL VERTICES OF ODD ORDER MUST BE MADE EVEN -- CREATE VECTOR?
		* COULD CREATE LOOPS -- MUST ENSURE HAMILTONIAN CIRCUIT -- USE SHORTCUTS
		* ALL VERTICES MUST HAVE EVEN ORDER
	*/

	// Print graph

	// Distance between vertices
	double distance(int x0, int y0, int x1, int y1) {}

	// Visited?

};

#endif

