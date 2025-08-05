/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	// Return number of elements in the vector
	return names.size();
}

bool VectorPriorityQueue::isEmpty() {
	// Check if vector is empty
	return size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	// Add new element to the end
	names.add(value);
}

string VectorPriorityQueue::peek() {
	// Return the minimum element without removing
	if (isEmpty()) {
		error("Vector is empty");
	}
	string result = names[0];
	for (int i = 1; i < names.size(); i++) {
		if (names[i] < result) {
			result = names[i];
		}
	}
	return result;
}

string VectorPriorityQueue::dequeueMin() {
	// Remove and return the minimum element
	string result = peek();
	int index = 0;
	for (int i = 1; i < names.size(); i++) {
		if (names[i] < names[index]) {
			index = i;
		}
	}
	names.remove(index);
	return result;
}