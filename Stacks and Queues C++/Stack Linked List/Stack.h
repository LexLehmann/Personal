// Stack.h    Author:Alex Lehmann
//Lists the functions that should be implemented in a queue
// and declares the varibles that will be needed to implement
// a linked list

template <typename E>
class Stack {
public:
	Stack();					//constructor
	Stack(const Stack &obj);	//copy constructor
	~Stack();					//destructor
	void push(const E& e);		//puts new value on top of the stack
	const E& pop();				//takes elem off the top of the stack and returns it
	const E& top() const;		//returns value on the top of the stack
	int size() const;			//returns size of the stack
	bool empty() const;			// returns true if stack is empty and false otherwise

private:
	struct Node {			// defines what a node on the linked list consists of
		E elem;
		Node* next;
	};
	Node* head;				// points to start of linked list
	int numElements;		// holds the number of elements in the stack
};