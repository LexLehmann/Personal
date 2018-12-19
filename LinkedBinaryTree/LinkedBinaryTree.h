#ifndef LINKEDBINARYTREE_H
#define LINKEDBINARYTREE_H

#include <string>
#include <list>
#include <functional>

using namespace std;

class LinkedBinaryTree {
protected:
	// insert Node declaration here...
	struct Node {					// a node of the tree
		string  elt;					// element value
		int count, avl;
		Node*   par;					// parent
		Node*   left;					// left child
		Node*   right;					// right child
		Node() : elt(""), par(NULL), left(NULL), right(NULL), count(0), avl(0) { } // constructor
	};
public:
	// insert Position declaration here...
	class Position {					// position in the tree
	private:
		Node* v;						// pointer to the node
	public:
		Position(Node* _v = NULL) : v(_v) { }		// constructor
		string& operator*()					// get element
		{
			return v->elt;
		}
		int count() const {
			return v->count;
		}
		Position left() const				// get left child
		{
			return Position(v->left);
		}
		Position right() const				// get right child
		{
			return Position(v->right);
		}
		Position parent() const				// get parent
		{
			return Position(v->par);
		}
		bool isRoot() const				// root of the tree?
		{
			return v->par == NULL;
		}
		bool isExternal() const				// an external node?
		{
			return v->left == NULL && v->right == NULL;
		}
		friend class LinkedBinaryTree;			// give tree access
	};
	typedef std::list<Position> PositionList;		// list of positions
public:
	LinkedBinaryTree();					// constructor
	int size() const;					// number of nodes
	bool empty() const;					// is tree empty?
	Position root() const;				// get the root
	PositionList prepositions() const;  			// list of nodes
	PositionList inpositions() const;  			// list of nodes
	void addRoot();					// add root to empty tree
	void expandExternal(const Position& p, string newinternal, string rightleaf, string leftleaf, bool newleafside);		// expand external node
	void insert(string input);		// input next string
	Position removeAboveExternal(const Position& p);	// remove p and parent
	void construct(Position& p, string* pre, string* in, int prestart, int preend, int instart, int inend);
	~LinkedBinaryTree();
	// housekeeping functions omitted...
protected: 						// local utilities
	void preorder(Node* v, PositionList& pl) const;	// preorder utility
	void inorder(Node* v, PositionList& pl) const;	// preorder utility
	void destroyLinkedBinaryTree(Node* v);
	void avlCorrection(Node* v);
	void rightRot(Node* v);
	void leftRot(Node* v);
	void rightLeftRot(Node* v);
	void leftRightRot(Node* v);
private:
	Node* _root;					// pointer to the root
	int n;						// number of nodes
};

#endif
