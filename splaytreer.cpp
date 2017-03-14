#include "splaytreer.h"
#include "node.h"
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdint>
using std::cout;
using std::endl;


Node * root;
int num_elements;
SplayTreer::SplayTreer() {
	// TBD:
	root = nullptr;

}

SplayTreer::~SplayTreer() {
	// TBD:
	if (root) { delete(root); }

}

void SplayTreer::insert(string k, unsigned int r) {
	assert(r > 0 && r <= num_elements + 1);
	root = insert(k, r, root);
	splay(root);
	num_elements++;
}

Node * SplayTreer::insert(string k, unsigned int r, Node* T) {
	assert(r > 0 && r <= num_elements + 1);
	if (T == nullptr)
	{
		return new Node(k);

	}
	Node* LS = T->get_left();
	unsigned int r1 = ((LS == nullptr) ? 0 : LS->get_size() + 1);
	if (r <= r1)
	{
		T->set_left(insert(k, r, T->get_left()));
	}
	else
	{
		T->set_right(insert(k, r - r1, T->get_right()));

	}
	T->update_size();
	return T;
}

void SplayTreer::rinsert(string k, unsigned int r) {
	assert(r > 0 && r <= num_elements + 1);
	root = rinsert(k, r, root);
	
	num_elements++;
}

Node * SplayTreer::rinsert(string k, unsigned int r, Node* T) {
	assert(r > 0 && r <= num_elements + 1);
	if (T == nullptr)
	{
		return new Node(k);

	}
	Node* LS = T->get_left();
	unsigned int r1 = ((LS == nullptr) ? 0 : LS->get_size() + 1);
	if (r <= r1)
	{
		T->set_left(insert(k, r, T->get_left()));
	}
	else
	{
		T->set_right(insert(k, r - r1, T->get_right()));

	}
	T->update_size();
	return T;
}

void SplayTreer::reverse(Node* re)
{
	re = root;
	if (re == null) {
        return;
    }

    Node* temp = re.right;
    re.right = re.left;
    re.left = temp;

    reverse(re.left);

    reverse(re.right);
	
}

string SplayTreer::select(unsigned int r) {
	root = select(root, r);
	return (root == nullptr) ? "" : root->get_key();
}

/* Second wrapper method to prevent stack overflow during recursion. Break once you reach maxdepth. */
Node* SplayTreer::select(Node* T, unsigned int r) {
	bool success = false;
	while (!success) {
		root = select(root, r, success, 0);
	}
	return root;
}

/* This funcion performs a recursive select (splays the selected element to the root). */
Node* SplayTreer::select(Node* T, unsigned int r, bool& success, unsigned int depth) {
	// Base case of null tree.
	if (T == nullptr) {
		success = true;
		return nullptr;
	}

	unsigned int total_size = (T == nullptr) ? 0 : T->get_size();
	assert(r > 0 && r <= total_size);			// Make sure that we are asking for a valid rank.

	// Another base case. If we have rached element at rank r.
	unsigned int T_rank = ((T->get_left() == nullptr) ? 0 : T->get_left()->get_size()) + 1;
	if (T_rank == r) {
		success = true;
		return T;
	}

	// Recursive case.

	// Figure out the ranks of subtree of children and grandchildren.
	Node* left = T->get_left();
	Node* right = T->get_right();
	Node* left_left = (left == nullptr) ? nullptr : left->get_left();
	Node* left_right = (left == nullptr) ? nullptr : left->get_right();
	Node* right_left = (right == nullptr) ? nullptr : right->get_left();
	Node* right_right = (right == nullptr) ? nullptr : right->get_right();

	unsigned int left_rank = (left == nullptr) ? 0 : ((left_left == nullptr ? 0 : left_left->get_size()) + 1);
	unsigned int right_rank = ((right == nullptr) ? 0 : ((right->get_left() == nullptr ? 0 : right_left->get_size()) + 1)) + T_rank;

	// Is the node with rank r one step away?
	Node* ret = nullptr;
	if (left_rank == r) {
		ret = left;
		rotate_left(T, left);
		success = true;
		return ret;
	}
	if (right_rank == r) {
		ret = right;
		rotate_right(T, right);
		success = true;
		return ret;
	}

	// Reached max depth in recursion?
	if (depth == max_depth)
		return T;

	// Is the node with rank r two or more steps away?
	// zig zig case
	if (r < left_rank) {
		ret = select(left_left, r, success, depth + 1);
		rotate_left(T, left);
		rotate_left(left, ret);
		return ret;
	}
	// zig zag case
	if (r > left_rank && r < T_rank) {
		ret = select(left_right, r - left_rank, success, depth + 1);
		rotate_right(left, ret);
		rotate_left(T, ret);
		return ret;
	}
	// zag zig case
	if (r > T_rank && r < right_rank) {
		ret = select(right_left, r - T_rank, success, depth + 1);
		rotate_left(right, ret);
		rotate_right(T, ret);
		return ret;
	}
	// zag zag case
	ret = select(right_right, r - right_rank, success, depth + 1);
	rotate_right(T, right);
	rotate_right(right, ret);
	return ret;
}
void SplayTreer::modify(unsigned int r, string k) {
	assert(r > 0 && r <= num_elements);
	string w1 = select(r);
	if (!(w1.empty()))
	{
		root->set_key(k);
	}
	else{ return; }
	// TBD:
}

void SplayTreer::split(unsigned int r, SplayTree* R) {
	assert(R != nullptr);						// R should be allocated by the user.
	assert(R->root == nullptr);			// The pointer to the right subtree should be nullptr.

	// Nothing to split if root is nullptr.
	if (root == nullptr)
		return;

	assert(r >= 0 && r <= num_elements);

	// Case when left side of split is empty (or rank = 0).
	if (r == 0) {
		R->root = root;
		R->num_elements = num_elements;
		root = nullptr;
		num_elements = 0;
		return;
	}

	// Normal case. Select and splay the element at rank r. Then split the right subtree.
	root = select(root, r);

	R->root = root->get_right();
	R->num_elements = (R->root == nullptr) ? 0 : R->root->get_size();

	root->set_right(nullptr);
	root->update_size();
	num_elements = root->get_size();
}

void SplayTreer::join(SplayTree* R) {
	assert(R != nullptr);					// R should be allocated by the user.
	Node * r1 = root;
	while (r1->get_right() != nullptr)
	{
		r1 = r1->get_right();
	}
	splay(r1);
	r1->set_right(R->root);
	// TBD:
}

void SplayTreer::print() {
	// TBD:

	InOrder(root);

	cout << "\n";
}

void SplayTreer::rotate(Node * A, Node * B) {
	Node * at1 = A->get_parent();
	if (A->get_left() == B)
	{
		A->set_left(B->get_right());
		B->set_right(A);


	}
	else {
		A->set_right(B->get_left());
		B->set_left(A);
	}
	if (!at1)
	{
		root = B;
		B->set_parent(nullptr);
	}
	else if (at1->get_left() == A)
	{
		at1->set_left(B);
	}
	else{
		at1->set_right(B);
	}
}



void SplayTreer::splay(Node * r1) {
	while (r1 != root)
	{
		Node * r2 = r1->get_parent();
		Node * r3 = r1->get_parent()->get_parent();

		if (r2 == root)
		{
			rotate(r2, r1);
			break;
		}

		if ((r3->get_left() && r3->get_left()->get_left() == r1) || (r3->get_right() && r3->get_right()->get_right() == r1))
		{
			rotate(r3, r2);
			rotate(r2, r1);

		}
		else{
			rotate(r2, r1);
			rotate(r3, r1);

		}
	}


}
void SplayTreer::InOrder(Node * root)
{
	if (root == nullptr)
	{
		return;
	}
	string w1 = root->get_key();
	InOrder(root->get_left());
	cout << w1 + " ";
	InOrder(root->get_right());
}


unsigned int SplayTree::size() {
	return num_elements;
}
bool isChildren(Node *root)
{
	bool cad;
	cad = 0;
	if((root->getleft() != null) || (root->getright() != null)
	{
     cad = 1;

	}
	return cad;
	
	
}
void SplayTreer::setNumberDescendants(Node *root)
{
	if (root == nullptr)
	{
		return;
		
	}
	while(isChildren(root) == true)
	{
		setNumberDescedants(root->getleft());
	if(root->getleft() != null)	
	{
		root.descendants += 1 + ((root->getleft()).descendants);
	}
	else if (root->getright() != null){
		root.descendants += 1 + ((root->getright()).descendants);
	}
	}
	setNumberDescendants(root->getright());
	
	
}
int SplayTreer::getNumberDescendants(Node * root)
{
	
	if(root == null)
		return;
	
	
    getNumberDescendants(root->parent);	
	if(reverse1)
	{
		numSearch += 1;
		
	}
	
	
}
uint SplayTreer::reverseBits(Node * root)
{
	
	string as = root->get_key();
	int num = atoi(as.c_str()); 
    unsigned int  NO_OF_BITS = sizeof(num) * 8;
    unsigned int reverse_num = 0;
    int i;
	
    for (i = 0; i < NO_OF_BITS; i++)
    {
        if((num & (1 << i)))
           reverse_num |= 1 << ((NO_OF_BITS - 1) - i);  
   }
   root.reverseBits();
    return reverse_num;
	
	
	
}
void SplayTreer::reverse(Node * ptr)
{
   if(ptr==null)
        return;
  else{
 if (numSearch % 2 == 1)
 {
  reverse(ptr->left);
  reverse(ptr->right);
  node* t= ptr->left;
  
  ptr->left=ptr->right;
  ptr->right=t;
  reverseBits(ptr->get_left());
  reverseBits(ptr->get_right());
  return;
 }
  
}
	return;
	
	
}