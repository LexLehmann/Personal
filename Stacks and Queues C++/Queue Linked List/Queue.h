// Queue.h    Author:Alex Lehmann
// Lists the functions that should be implemented in a queue
// and declares the varibles that will be needed to implement
// a linked list

template <typename E>
class Queue {
public:
	Queue();					//constructor
	Queue(const Queue &obj); 	//copy constructor 
	~Queue();					//destructor
	void enqueue(const E& e);	//Puts new value at back of queue
	const E& dequeue();			 //takes value off front of queue and retruns value
	const E& front() const;		//returns the front of the queue
	int size() const;			//returns the length of the queue
	bool empty() const;			//returns true if queue is empty and false otherwise

private:
	struct Node {				// defines what a node on the linked list consists of
		E elem;
		Node* next;
	};
	Node* head;					// points to start of the linked list
	Node* tail;					// points to the end of the linked list
	int numElements;			// stores the number of values in the queue
};