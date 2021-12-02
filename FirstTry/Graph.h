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
    vector<pair<int, edge> > G;  // graph
    vector<pair<int, edge> > T;  // mst
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
    void union_set(int u, int v);
    void kruskal();
    void print();
    vector<pair<int, edge>> getMST();
};
Graph::Graph(int V) {
    parent = new int[V];

    //set parent to be 0,1,2,3,....v
    for (int i = 0; i < V; i++)
        parent[i] = i;
    //clear the grah and minimum spanning tree on initiantion
    G.clear();
    T.clear();
    weight = 0;
}
void Graph::addEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        //recursibly call find_set to find the parent.
        return find_set(parent[i]);
}

//set the parent of u to be v
void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}

//Kruskals algorithm
void Graph::kruskal() {
    int i, uRep, vRep;
    //Sort the graph so the weight is in an increasing order
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