/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	// Initialize empty list
	length = 0;
	first = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// Free all nodes
	Cell* tmp;
	while (first != NULL) {
		tmp = first;
		first = first->next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	// Return number of elements
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	// Check if list is empty
	return length == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	// Insert new element at the front
	Cell* currCell = new Cell;
	currCell->name = value;
	currCell->back = NULL;
	currCell->next = first;

	if (first != NULL) {
		first->back = currCell;
	}
	first = currCell;
	length++;
}

string DoublyLinkedListPriorityQueue::peek() {
	// Return the minimum value without removing
	if (isEmpty()) {
		error("queue is empty");
	}
	Cell* current = first;
	string ans = current->name;

	while (current != NULL) {
		if (current->name < ans) {
			ans = current->name;
		}
		current = current->next;
	}
	return ans;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	// Remove and return the minimum value
	string ans = peek();
	Cell* curr = first;
	while (curr != NULL) {
		if (curr->name == ans) {
			break;
		}
		curr = curr->next;
	}
	length--;
	deleteCell(curr);
	return ans;
}

void DoublyLinkedListPriorityQueue::deleteCell(Cell* curr) {
	// Remove cell from the list and fix links
	if (curr->back != NULL) {
		curr->back->next = curr->next;
	}
	else {
		first = curr->next;
	}
	if (curr->next != NULL) {
		curr->next->back = curr->back;
	}
	delete curr;
}