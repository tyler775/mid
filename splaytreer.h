#ifndef SPLAYTREER_H
#define SPLAYTREER_H

#include "node.h"

/*
This represents a SplayTree that encodes a dynamic sequence.
*/
class SplayTreer {
	Node* root;										// The root node of the Splay Tree.
	unsigned int num_elements;						// The number of elements stored in the tree.

public:
	SplayTreer();									// Constructs a Splay Tree. Initializes the root to nullptr and num_elements to 0.
	~SplayTreer();									// De-allocates all the nodes in the Tree.
	void insert(string k, unsigned int r);			// inserts string k at position r.
	Node * insert(string k, unsigned int r, Node * T);
	void rinsert(string k, unsigned int r);			// inserts string k at position r.
	Node * rinsert(string k, unsigned int r, Node * T);
	string select(unsigned int r);					// Selects the element at position r (splays it to the root).
	Node* select(Node*, unsigned int);
	Node* select(Node*, unsigned int, bool&, unsigned int);
	void modify(unsigned int r, string k);			// Modifies the element at position r to string k.
	void split(unsigned int r, SplayTree* R);		// Splits the tree at position r. The left side of the split is stored in the calling object. The right side of the split is stored in R.
	void join(SplayTree*);							// Concatenates the sequences stored in the current tree (calling object) with R.

	void print();
	void rotate(Node * s1, Node * s2);
	void splay(Node * r1);
	void InOrder(Node * root);	// Prints the sequence by doing an inorder traversal of the tree.
	unsigned int size();							// Returns the number of elements currently stored in the tree.
	void setNumberDescendants(Node *root);
	int getNumberDescendants(Node *root);
	uint reverseBits(Node * root);
	void reverse(Node * ptr);
	// Private recursive functions to implement the above.
private:
	// Fill in your own private methods, and other private data that suits your implementation.
	// TBD...

};

#endif