#include <iostream>
#include "Graph.h"
#include "EulerianTour.h"
#include <stack>
#include <iostream>
#include <fstream>

// Using base code from https://www.geeksforgeeks.org/preorder-traversal-of-n-ary-tree-without-recursion/
// for preorder traversal.

std::vector <int> preTraversal;

struct Node {
	int pos;
	vector<Node*> child;
};

Node* addNode(int pos)
{
	Node* temp = new Node;
	temp->pos = pos;
	return temp;
}

void traverse_tree(struct Node* root)
{
	// Stack to store the nodes
	stack<Node*> nodes;

	// push the current node onto the stack
	nodes.push(root);

	// loop while the stack is not empty
	while (!nodes.empty()) {

		// store the current node and pop it from the stack
		Node* curr = nodes.top();
		nodes.pop();

		// current node has been travarsed
		if (curr != NULL)
		{
			cout << curr->pos << " ";
			preTraversal.push_back(curr->pos);

			// store all the childrent of current node from right to left.
			vector<Node*>::iterator it = curr->child.end();

			while (it != curr->child.begin()) {
				it--;
				nodes.push(*it);
			}
		}
	}
}


int main() {

		vector<pair<int, edge> > MST;

		int numVert = 7;
		Graph test(numVert);
		// ADD EDGES
		test.addEdge(0, 1, 1);
		test.addEdge(0, 2, 2);
		test.addEdge(0, 3, 3);
		test.addEdge(0, 4, 4);
		test.addEdge(0, 5, 5);
		test.addEdge(0, 6, 6);

		test.addEdge(1, 2, 7);
		test.addEdge(1, 3, 8);
		test.addEdge(1, 4, 9);
		test.addEdge(1, 5, 10);
		test.addEdge(1, 6, 11);

		test.addEdge(2, 3, 12);
		test.addEdge(2, 4, 13);
		test.addEdge(2, 5, 14);
		test.addEdge(2, 6, 15);

		test.addEdge(3, 4, 16);
		test.addEdge(3, 5, 17);
		test.addEdge(3, 6, 18);

		test.addEdge(4, 5, 19);
		test.addEdge(4, 6, 20);

		test.addEdge(5, 6, 21);

		if (!test.sameWeights()) {
        // CONSTRUCT MINIMUM SPANNING TREE
        test.kruskal();
        MST = test.getMST();
		std::ofstream file;
		file.open("graph.txt");
		for (int i = 0; i < MST.size(); i++) {
			file << MST[i].second.first << " " << MST[i].second.second << " "
				<< MST[i].first;
			file << std::endl;
		}

		file.close();


		Node* root = addNode(0);
		(root->child).push_back(addNode(1));
		(root->child).push_back(addNode(2));
		(root->child).push_back(addNode(3));
		(root->child).push_back(addNode(4));
		(root->child).push_back(addNode(5));
		(root->child).push_back(addNode(6));
		/*(root->child[0]->child).push_back(newNode(10));*/

		traverse_tree(root);

        EulerianTour eulerian(MST, numVert);

        eulerian.printMST();

		eulerian.hamilton(preTraversal,test);
		eulerian.printHamiltonianCircuit();

    }
    else {
        cout << "weights are the same, order does not matter just go down the line";
    }

	return 0;
}
