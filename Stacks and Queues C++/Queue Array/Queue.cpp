// Queue.cpp    Author:Alex Lehmann
//implements a queue using a circular array

#include "Queue.h"

//constructor
template <typename E>
Queue<E>::Queue() {
	arraySize = 1;
	queue = new E[arraySize];
	begin = -1;
	rear = -1;
}

//copy constructor 
template <typename E>
Queue<E>::Queue(const Queue &obj) {
	arraySize = 1;
	queue = new E[arraySize];
	begin = -1;
	rear = -1;
	for (int i = 0; i < obj.size(); i++) {
		enqueue(obj.queue[(obj.begin) + i]);
	}
}

//destructor
template <typename E>
Queue<E>::~Queue() {
	while (!empty()) {
		dequeue();
	}
	delete[] queue;
}

//Puts new value at back of queue
// doubles the size of the array when it is full
template <typename E>
void Queue<E>::enqueue(const E& e) {
	if (empty()) {
		begin = 0;
		rear = 0;
	}
	else {
		rear++;
		rear = rear % arraySize;
		if (begin == rear) {
			E* temp = queue;
			queue = new E[arraySize * 2];
			for (int i = 0; i < arraySize; i++) {
				queue[i] = temp[(begin + i) % arraySize];
			}
			delete[] temp;
			begin = 0;
			rear = arraySize;
			arraySize = arraySize * 2;
		}
	}


	queue[rear] = e;
}

//takes value off front of queue and returns value
template <typename E>
const E& Queue<E>::dequeue() {
	if (empty()) {

	}
	int val = begin;
	begin++;
	begin = begin % arraySize;
	if (begin == (rear + 1)) {
		begin = -1;
	}
	return queue[val];
}

//returns the front of the queue
template <typename E>
const E& Queue<E>::front() const {
	if (empty()) {

	}
	return queue[begin];
}

//returns the length of the queue
template <typename E>
int Queue<E>::size() const {
	int num;
	num = rear - begin + 1;
	if (num <= 0) {
		num += arraySize;
	}
	return num;
}

//returns true if queue is empty and false otherwise
template <typename E>
bool Queue<E>::empty() const {
	return begin == -1;
}