// LinkedBinaryTree.cpp       Author : Alex Lehmann
// This operates a Linked Binary Tree

#include "LinkedBinaryTree.h"
#include <functional>

// Constructor
LinkedBinaryTree::LinkedBinaryTree() {			// constructor
	_root = NULL;
	n = 0;
}

// Deconstructor
LinkedBinaryTree::~LinkedBinaryTree() {
	destroyLinkedBinaryTree(_root);
}

// helps the deconstructor does most of the work  recusivlly calls
void LinkedBinaryTree::destroyLinkedBinaryTree(Node* v) {
	if (v != NULL) {
		destroyLinkedBinaryTree(v->right);
		destroyLinkedBinaryTree(v->left);
		delete v;
		n--;
	}
}

// returns the size of the tree
int LinkedBinaryTree::size() const			// number of nodes
{
	return n;
}

// returns true if the tree is empty
bool LinkedBinaryTree::empty() const			// is tree empty?
{
	return size() == 0;
}

// returns the root of the tree
LinkedBinaryTree::Position LinkedBinaryTree::root() const // get the root
{
	return Position(_root);
}

// adds a new root. sould only be called if tree is empty
void LinkedBinaryTree::addRoot()			// add root to empty tree
{
	_root = new Node;
}

// inserts a word into the tree. if already in increments counter.
// if it isn't it uses avl to know when to rebalance the tree
void LinkedBinaryTree::insert(string input) {
	Position p = _root;
	bool test = true;
	if (*p == "") {
		*p = input;
		n = 1;
		p.v->count = 1;
	}
	else {
		while (*p != input && !p.isExternal() && test) {
			//cout << "test" << endl;
			if (*p > input) {
				if (p.v->left == NULL) {
					test = false;
				}
				else {
					p = p.left();
				}
			}
			else {
				if (p.v->right == NULL) {
					test = false;
				}
				else {
					p = p.right();
				}
			}
		}
		if (*p == input) {
			p.v->count++;
		}
		else {
			Node* g = new Node;
			g->elt = input;
			g->par = p.v;
			g->count = 1;
			g->avl = 0;
			n++;
			if (*p > g->elt) {
				p.v->left = g;
			}
			else {
				p.v->right = g;
			}
			//avlCorrection(g);
		}
	}
}

// expand external node
void LinkedBinaryTree::expandExternal(const Position& p, string newinternal, string leaf1, string leaf2, bool newleafside) {
	Node* v = p.v;					// p's node
	v->left = new Node;					// add a new left child
	v->left->par = v;					// v is its parent
	v->right = new Node;				// and a new right child
	v->right->par = v;					// v is its parent
	if (newleafside == true) {
		v->right->elt = leaf1;
		v->left->elt = leaf2;
	}
	else {
		v->left->elt = leaf1;
		v->right->elt = leaf2;
	}
	v->elt = newinternal;
	n += 2;						// two more nodes
}

LinkedBinaryTree::Position				// remove p and parent
LinkedBinaryTree::removeAboveExternal(const Position& p) {
	Node* w = p.v;  Node* v = w->par;			// get p's node and parent
	Node* sib = (w == v->left ? v->right : v->left);
	if (v == _root) {					// child of root?
		_root = sib;					// ...make sibling root
		sib->par = NULL;
	}
	else {
		Node* gpar = v->par;				// w's grandparent
		if (v == gpar->left)
			gpar->left = sib; 		// replace parent by sib
		else gpar->right = sib;
		sib->par = gpar;
	}
	delete w; delete v;					// delete removed nodes
	n -= 2;						// two fewer nodes
	return Position(sib);
}

// sets the avl values after an insert. calls a rotation
// when it needs to
void LinkedBinaryTree::avlCorrection(Node* v) {
	Node* trailer;
	do {
		//cout << "blarg" << endl;
		trailer = v;
		v = v->par;
		if (v->left == trailer) {
			v->avl--;
		}
		else {
			v->avl++;
		}

		if (v->avl == -2) {
			if (trailer->avl < 0) {
				rightRot(v);
			}
			else {
				leftRightRot(v);
			}
		}
		else if(v->avl == 2) {
			if (trailer->avl < 0) {
				rightLeftRot(v);
			}
			else {
				leftRot(v);
			}
		}
	} while (v->avl != 0 && v != _root);
}

// does a right rotate about given node
void LinkedBinaryTree::rightRot(Node* v) {
	Node* child = v->left;
	Node* childRight = child->right;

	child->par = v->par;
	if (v != _root) {
		if (v == v->par->left) {
			v->par->left = child;
		}
		else {
			v->par->right = child;
		}
	}
	else {
		_root = child;
	}
	v->par = child;
	child->right = v;
	if (childRight != NULL) {
		childRight->par = v;
	}
	v->left = childRight;

	child->avl = 0;
	v->avl = 0;
}

// does a left rotate about a given node
void LinkedBinaryTree::leftRot(Node* v) {
	Node* child = v->right;
	Node* childLeft = child->left;

	child->par = v->par;
	if (v != _root) {
		if (v == v->par->left) {
			v->par->left = child;
		}
		else {
			v->par->right = child;
		}
	}
	else {
		_root = child;
	}
	v->par = child;
	child->left = v;

	if (childLeft != NULL) {
		childLeft->par = v;
	}
	v->right = childLeft;

	child->avl = 0;
	v->avl = 0;
}

// does a left right rotate about a given node
// sets the avl values to the correct one after the rotate
void LinkedBinaryTree::leftRightRot(Node* v) {
	int val = 0;
	if (v->left->right->avl == -1) {
		val = 1;
	}
	else if (v->left->right->avl == 1) {
		if (v->left->right->right->avl = -1) {
			val = 2;
		}
		else {
			val = 3;
		}
	}
	leftRot(v->left);
	rightRot(v);
	switch (val) {
	case 1:
		v->avl = -1;
		break;
	case 2:
		v->par->left->avl = 1;
		break;
	case 3:
		v->par->left->avl = -1;
		break;
	default:
		break;
	}
}

// does a right left rotate about a given node
// sets the avl values to the correct one after the rotate
void LinkedBinaryTree::rightLeftRot(Node* v) {
	int val = 0;
	if (v->right->left->avl == 1) {
		val = 1;
	}
	else if (v->right->left->avl == -1) {
		if (v->right->left->left->avl = 1) {
			val = 2;
		}
		else {
			val = 3;
		}
	}
	rightRot(v->right);
	leftRot(v);
	switch (val) {
	case 1:
		v->avl = -1;
		break;
	case 2:
		v->par->right->avl = 1;
		break;
	case 3:
		v->par->right->avl = -1;
		break;
	default:
		break;
	}
}

// list of all nodes preorder calls preorder
LinkedBinaryTree::PositionList LinkedBinaryTree::prepositions() const {
	PositionList pl;
	preorder(_root, pl);					// preorder traversal
	return PositionList(pl);				// return resulting list
}

// list of all nodes calls inorder
LinkedBinaryTree::PositionList LinkedBinaryTree::inpositions() const {
	PositionList pl;
	inorder(_root, pl);					// preorder traversal
	return PositionList(pl);				// return resulting list
}

// preorder traversal
void LinkedBinaryTree::preorder(Node* v, PositionList& pl) const {
	pl.push_back(Position(v));				// add this node
	if (v->left != NULL)					// traverse left subtree
		preorder(v->left, pl);
	if (v->right != NULL)					// traverse right subtree
		preorder(v->right, pl);
}

// inorder traversal
void LinkedBinaryTree::inorder(Node* v, PositionList& pl) const {
	if (v->left != NULL)					// traverse left subtree
		inorder(v->left, pl);
	pl.push_back(Position(v));				// add this node
	if (v->right != NULL)					// traverse right subtree
		inorder(v->right, pl);
}