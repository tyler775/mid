
#include <iostream>
using std::endl;
using std::cout;
using std::cin;

#include <string>
using std::string;

#include <sstream>

#include "splaytree.h"

void cut_paste(SplayTree *T, int i, int j, int k) {
	SplayTree *A = new SplayTree();
	SplayTree *B = new SplayTree();
	SplayTree *C = new SplayTree();

	T->split(j, B);
	T->split(i-1, A);

	if (k >= j) {
		B->split(k-j, C);
		T->join(B);
		T->join(A);
		T->join(C);
	}
	else {
		T->split(k, C);
		T->join(A);
		T->join(C);
		T->join(B);
	}
	delete C;
	delete B;
	delete A;
}

int main() {
	
	string line;
	string word;
	SplayTree *T = new SplayTree();
	int num_words = 1;
	string newline = "\n";
	
	int n;			// Number of lines.
	cin >> n;
	getline(cin, line);
	
	for (int i = 0; i < n; i++) {
		
		getline(cin, line);
		std::istringstream iss(line);
		
		// while there are words in the line...
		while (iss >> word) {
			T->insert(word, num_words++);
		}
		T->insert("\n", num_words++);
		iss.clear();
	}

	int m;				// Number of queries.
	int i, j, k;	// Variables to hold each query.
	cin >> m;

	for (int x = 0; x < m; x++) {
		cin >> i >> j >> k;		
		cut_paste(T, i, j, k);
	}
	T->print();
	
	delete T;
	return 0;
}
