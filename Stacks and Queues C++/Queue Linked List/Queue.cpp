// Queue.cpp    Author:Alex Lehmann
//implements a queue using a linked list

#include "Queue.h"
#include<stdio.h>

//constructor
template <typename E>
Queue<E>::Queue() {
	numElements = 0;
	head = NULL;
	tail = NULL;
}

//copy constructor 
template <typename E>
Queue<E>::Queue(const Queue &obj) {
	Node* cur = obj.head;
	for (int i = 0; i < obj.size(); i++) {
		enqueue(cur->elem);
		cur = cur->next;
	}
}

//destructor
template <typename E>
Queue<E>::~Queue() {
	while (!empty()) {
		dequeue();
	}
}

//Puts new value at back of queue
template <typename E>
void Queue<E>::enqueue(const E& e) {
	Node* val = new Node;
	val->elem = e;
	val->next = NULL;
	if (empty()) {
		head = val;
		tail = val;
	}
	else {
		tail->next = val;
		tail = val;
	}
	numElements++;
}

//takes value off front of queue and returns value
template <typename E>
const E& Queue<E>::dequeue() {
	if (empty()) {

	}
	Node* val = new Node;
	val = head;
	head = head->next;
	numElements--;
	E elem = val->elem;
	delete val;
	return elem;
}

//returns the front of the queue
template <typename E>
const E& Queue<E>::front() const {
	if (empty()) {

	}
	return head->elem;
}

//returns true if queue is empty and false otherwise
template <typename E>
bool Queue<E>::empty() const {
	return numElements == 0;
}

//returns the length of the queue
template <typename E>
int Queue<E>::size() const {
	return numElements;
}