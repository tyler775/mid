#include "node.h"

Node::Node(string k) {
	key = k;
	left = right = nullptr;
	size = 1;
	descendants = 0;
	reverse1 = 0;
}

void Node::update_size() {
	size = ((left == nullptr) ? 0 : left->size) + ((right == nullptr) ? 0 : right->size) + 1;
}

string Node::get_key() {
	return key;
}

unsigned int Node::get_size() {
	return size;
}

Node* Node::get_left() {
	return left;
}

Node* Node::get_right() {
	return right;
}

void Node::set_key(string k) {
	key = k;
}

void Node::set_left(Node* l) {
	left = l;
}

void Node::set_right(Node* r) {
	right = r;
}
void Node::reversebit(){
	if(reverse1 == 0)
	{
	reverse1 = 1;
    }
	else{
		reverse1 = 0;
	}

}
