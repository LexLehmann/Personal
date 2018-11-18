// Stack.cpp    Author:Alex Lehmann
//implements a stack using a linked list

#include "Stack.h"
#include<stdio.h>

//constructor
template <typename E>
Stack<E>::Stack() {
	numElements = 0;
	head = NULL;
}

//copy constructor
// copy keeps track of value that will be copied next
//cur keeps track of place in list being built
template <typename E>
Stack<E>::Stack(const Stack &obj) {
	Node* copy = obj.head;
	Node* cur;
	head = new Node;
	head->elem = copy->elem;
	head->next = NULL;
	cur = head;
	for (int i = 0; i < obj.size() - 1; i++) {
		copy = copy->next;
		Node* temp = new Node;
		temp->elem = copy->elem;
		cur->next = temp;
		temp->next = NULL;
		cur = cur->next;
	}
}

// deconstructor
template <typename E>
Stack<E>::~Stack() {
	while (!empty()) {
		pop();
	}
}

// puts a new value on top of the stack
template <typename E>
void Stack<E>::push(const E& e) {
	Node* val = new Node;
	val->elem = e;
	if (empty()) {
		val->next = NULL;
	}
	else {
		val->next = head;
	}
	head = val;
	numElements++;
}

// takes top value off the stack and returns it
template <typename E>
const E& Stack<E>::pop() {
	Node* val = new Node;
	val = head;
	head = head->next;
	numElements--;
	E elem = val->elem;
	delete val;
	return elem;
}

// returns the value on the top of the stack
template <typename E>
const E& Stack<E>::top() const {
	return head->elem;
}

// returns true if stack is empty and false otherwise
template <typename E>
bool Stack<E>::empty() const {
	return numElements == 0;
}

//returns the size of the stack
template <typename E>
int Stack<E>::size() const {
	return numElements;
}