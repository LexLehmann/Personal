#include "LinkedBinaryTree.h"
#include <functional>

LinkedBinaryTree::LinkedBinaryTree() {			// constructor
	_root = NULL;
	n = 0;
}

LinkedBinaryTree::~LinkedBinaryTree() {
	Node* v = _root;
	if (v->left != NULL)					
		destroyLinkedBinaryTree(v->left);
	if (v->right != NULL)					
		destroyLinkedBinaryTree(v->right);
	delete v->left;
	delete v->right;
	delete v->par;
	delete v;
	n--;
}

void LinkedBinaryTree::destroyLinkedBinaryTree(Node* v) {
	if (v->left != NULL)
		destroyLinkedBinaryTree(v->left);
	if (v->right != NULL)
		destroyLinkedBinaryTree(v->right);
	delete v->left;
	delete v->right;
	delete v->par;
	delete v;
	n--;
}

int LinkedBinaryTree::size() const			// number of nodes
{
	return n;
}

bool LinkedBinaryTree::empty() const			// is tree empty?
{
	return size() == 0;
}

LinkedBinaryTree::Position LinkedBinaryTree::root() const // get the root
{
	return Position(_root);
}

void LinkedBinaryTree::addRoot()			// add root to empty tree
{
	_root = new Node;
}

void LinkedBinaryTree::insert(string input) {
	Position p = _root;
	bool test = true;
	if (*p == "") {
		*p = input;
		n = 1;
	}
	else {
		while (*p != input && !p.isExternal() && test) {
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
			avlCorrection(g);
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

void LinkedBinaryTree::construct(Position& p, string* pre, string* in, int preStart, int preEnd, int inStart, int inEnd) {
	int rightPreStart = preStart, rightPreEnd = preEnd, rightInStart = inStart, rightInEnd = inEnd;
	int leftPreStart = preStart, leftPreEnd = preEnd, leftInStart = inStart, leftInEnd = inEnd;
	if (inStart < inEnd&&preStart < preEnd) {
		while (pre[leftPreStart] != in[leftInEnd]) {
			--leftInEnd;
		}
		rightPreStart = leftInEnd + 1;
		leftPreStart++;

		expandExternal(p, in[leftInEnd], pre[leftPreStart], in[rightPreStart], false);

		leftPreEnd = leftInEnd;
		--leftInEnd;
		rightInStart = rightPreStart;

		construct(p.left(), pre, in, leftPreStart, leftPreEnd, leftInStart, leftInEnd);
		construct(p.right(), pre, in, rightPreStart, rightPreEnd, rightInStart, rightInEnd);
	}
}

void LinkedBinaryTree::avlCorrection(Node* v) {
	Node* trailer;
	bool rotated = false;
	do {
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
		else if(v->avl == 2){
			if (trailer->avl < 0) {
				rightLeftRot(v);
			}
			else {
				leftRot(v);
			}
		}
	} while (v->avl != 0 && v != _root);
}

void LinkedBinaryTree::rightRot(Node* v) {
	Node* parent = v;
	v = v->left;

	v->par = parent->par;
	if (v->right != NULL) {
		parent->left = v->right;
	}
	v->right = parent;


	v->avl = v->avl - 1;
	parent->avl = parent->avl - 2;
}

void LinkedBinaryTree::leftRot(Node* v) {
	Node* parent = v;
	v = v->right;

	v->par = parent->par;
	if (v->left != NULL) {
		parent->right = v->left;
	}
	v->left = parent;


	v->avl = v->avl - 1;
	parent->avl = parent->avl - 2;
}

void LinkedBinaryTree::leftRightRot(Node* v) {
	leftRot(v->left);
	rightRot(v);
}

void LinkedBinaryTree::rightLeftRot(Node* v) {
	rightRot(v->right);
	leftRot(v);
}

// list of all nodes
LinkedBinaryTree::PositionList LinkedBinaryTree::prepositions() const {
	PositionList pl;
	preorder(_root, pl);					// preorder traversal
	return PositionList(pl);				// return resulting list
}

// list of all nodes
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