// Queue.h    Author:Alex Lehmann
//Lists the functions that should be implemented in a queue
// and declares the varibles that will be needed to implement
// an array

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
	E* queue;					// points to the array
	int begin;					// stores index of current start of queue
	int rear;					// stores index of current end of queue
	int arraySize;				// stores the max size of current array
};