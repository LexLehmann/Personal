// Stack.cpp    Author:Alex Lehmann
//implements a stack using an array

#include "Stack.h"

//constructor
template <typename E>
Stack<E>::Stack() {
	numElements = 0;
	arraySize = 1;
	stack = new E[arraySize];
}

//copy constructor
template <typename E>
Stack<E>::Stack(const Stack &obj) {
	arraySize = 1;
	stack = new E[arraySize];
	numElements = 0;
	for (int i = 0; i < obj.size(); i++) {
		push(obj.stack[i]);
	}
}

// deconstructor
template <typename E>
Stack<E>::~Stack() {
	while (!empty()) {
		pop();
	}
	delete[] stack;
}

// puts a new value on top of the stack
// doubles the size of the array when it is full
template <typename E>
void Stack<E>::push(const E& e) {
	if (numElements == arraySize) {
		E* temp = stack;
		stack = new E[arraySize * 2];
		for (int i = 0; i < arraySize; i++) {
			stack[i] = temp[i];
		}
		delete[] temp;
		arraySize = arraySize * 2;
	}
	stack[numElements] = e;
	numElements++;
}

// takes top value off the stack and returns it
template <typename E>
const E& Stack<E>::pop() {
	--numElements;
	return stack[numElements];
}

// returns the value on the top of the stack but doesn't remove it
template <typename E>
const E& Stack<E>::top() const {
	if (empty()) {

	}
	return stack[numElements - 1];
}

//returns the size of the stack
template <typename E>
int Stack<E>::size() const {
	return numElements;
}

// returns true if stack is empty and false otherwise
template <typename E>
bool Stack<E>::empty() const {
	return numElements == 0;
}