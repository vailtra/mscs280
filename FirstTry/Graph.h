#ifndef GRAPH_H
#define GRAPH_H
// Kruskal's algorithm in C++

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge> > G;
    vector<pair<int, edge> > T;
    int* parent;
    //vertices in the graph
    int V;
    int weight;
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    int find_set(int i);
    int getMinimumWeight();
    int getWeight(int vert1, int vert2);
    bool sameWeights();
    void union_set(int u, int v);
    void kruskal();
    void print();
    vector<pair<int, edge>> getMST();
};
Graph::Graph(int V) {
    parent = new int[V];

    //Set parent to be 0-V
    for (int i = 0; i < V; i++)
        parent[i] = i;
    //clear the grah and minimum spanning tree on initiantion
    G.clear();
    T.clear();
    weight = 0;
}
//add edges to our graph
void Graph::addEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}
// Union find set
int Graph::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        //recursivly call find_set to find the parent.
        return find_set(parent[i]);
}

//set the parent of u to be v
void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}

//Kruskals algorithm
void Graph::kruskal() {
    int i, uRep, vRep;
    //Sort the graph by weight
    sort(G.begin(), G.end());
    //Loop through G
    for (i = 0; i < G.size(); i++) {
        //Set uRep and vRep to be the vertices at this locaton.
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            //Add edge to MST
            T.push_back(G[i]);

            union_set(uRep, vRep);
        }
    }
}

//Prints out the current minimum spanning tree
// t.second.first is first vertex, t.second.second is second vertex t.first is the edge value
void Graph::print() {
    cout << "Edge :"
        << " Weight" << endl;
    //Loop through MST
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : "
            << T[i].first;
        cout << endl;
    }
}

//Return the total weight of the minimum spanning tree
int Graph::getMinimumWeight() {
    for (int i = 0; i < T.size(); i++) {
        weight += T[i].first;
    }
    return weight;
}

// Check to see each edge has the same weight
bool Graph::sameWeights() {
    int temp = G[0].first;
    // loop through the graph
    for (int i = 1; i < G.size(); i++) {
        if (G[i].first != temp) {
            return false;
        }
    }
    return true;
}

//get weight of an edge between two different vertices
int Graph::getWeight(int vert1, int vert2) {
    //loop through the graph G
    for (int i = 0; i < G.size(); i++) {
        //if vert1 or vert 2 equals the first vertex at the current iteration and vert1 or vert2 equals the second vertex at the current iteration
        if ((G[i].second.first == vert1 || G[i].second.first == vert2) && (G[i].second.second == vert1 || G[i].second.second == vert2)) {
            //return the weight of the edge
            return G[i].first;
        }
    }
    //no matches were found, return 0
    return 0;
}

//Returns the minimum spanning tree
vector<pair<int, edge>> Graph::getMST() {
    return T;
}

#endif