/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	// Initialize with small fixed capacity
	count = 0;
	length = 2;
	heap = new string[length];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	// Free allocated memory
	delete[] heap;
}

int HeapPriorityQueue::size() {
	// Return current number of elements
	return count;
}

bool HeapPriorityQueue::isEmpty() {
	// Check if queue is empty
	return count == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	// Add new element, resize if needed
	if (count == length) {
		resizeStorage();
	}
	heap[count] = value;
	bubbleUp(count);
	count++;
}

string HeapPriorityQueue::peek() {
	// Return min element without removing
	if (isEmpty()) {
		error("queue is empty");
	}
	return heap[0];
}

string HeapPriorityQueue::dequeueMin() {
	// Remove and return min element (at root)
	string ans = peek();
	heap[0] = heap[count - 1];
	count--;
	bubbleDown(0);
	return ans;
}

void HeapPriorityQueue::resizeStorage() {
	// Double the array capacity
	length *= 2;
	string* newHeap = new string[length];
	for (int i = 0; i < count; i++) {
		newHeap[i] = heap[i];
	}
	delete[] heap;
	heap = newHeap;
}

void HeapPriorityQueue::bubbleUp(int index) {
	// Move element up to restore heap property
	while (index > 0) {
		int mother = (index - 1) / 2;
		if (heap[index] < heap[mother]) {
			swapStrings(heap[index], heap[mother]);
			index = mother;
		}
		else {
			break;
		}
	}
}

void HeapPriorityQueue::bubbleDown(int index) {
	// Move element down to restore heap property
	while (true) {
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int smallest = index;

		if (left < count && heap[left] < heap[smallest]) {
			smallest = left;
		}
		if (right < count && heap[right] < heap[smallest]) {
			smallest = right;
		}

		if (smallest != index) {
			swapStrings(heap[index], heap[smallest]);
			index = smallest;
		}
		else {
			break;
		}
	}
}

void HeapPriorityQueue::swapStrings(string& a, string& b) {
	// Swap two strings
	string temp = a;
	a = b;
	b = temp;
}