/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	// Initialize empty list
	first = NULL;
	length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	// Free all nodes
	Cell* tmp;
	while (first != NULL) {
		tmp = first;
		first = first->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	// Return number of elements
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	// Check if list is empty
	return length == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	// Insert element in sorted order
	Cell* newCell = new Cell;
	newCell->name = value;
	newCell->next = NULL;

	// Insert at beginning if list is empty or value is smallest
	if (first == NULL || value < first->name) {
		newCell->next = first;
		first = newCell;
	}
	else {
		// Find correct position
		Cell* current = first;
		while (current->next != NULL && current->next->name < value) {
			current = current->next;
		}
		newCell->next = current->next;
		current->next = newCell;
	}
	length++;
}

string LinkedListPriorityQueue::peek() {
	// Return smallest element without removing
	if (isEmpty()) {
		error("queue is empty");
	}
	return first->name;
}

string LinkedListPriorityQueue::dequeueMin() {
	// Remove and return smallest element (at head)
	string result = peek();
	Cell* tmp = first;
	first = first->next;
	delete tmp;
	length--;
	return result;
}

