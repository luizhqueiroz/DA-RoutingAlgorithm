/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

/**
* @file MutablePriorityQueue.h
* @brief Provides a mutable priority queue for Dijkstra's algorithm.
* @author Luiz, Pedro e Raphael
* @date 02/06/2023
*/


#include <vector>



/**
 * class T must have: (i) accessible field int queueIndex; (ii) operator< defined.
 */

template <class T>
class MutablePriorityQueue {
	std::vector<T *> H;
	void heapifyUp(unsigned i);
	void heapifyDown(unsigned i);
	inline void set(unsigned i, T * x);
public:

    /**
    * @brief Constructs an empty MutablePriorityQueue object.
    */
	MutablePriorityQueue();

    /**
    * @brief Inserts an element into the priority queue.
    * @param x A pointer to the element to be inserted.
    */
	void insert(T * x);

    /**
    * @brief Extracts the minimum element from the priority queue.
    * @return A pointer to the minimum element.
    */
	T * extractMin();

    /**
    * @brief Decreases the key of an element in the priority queue.
    * @param x A pointer to the element whose key is to be decreased.
    */
	void decreaseKey(T * x);

    /**
    * @brief Checks if the priority queue is empty.
    * @return `true` if the priority queue is empty, `false` otherwise.
    */
	bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
	H.push_back(nullptr);
	// indices will be used starting in 1
	// to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
	return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
	auto x = H[1];
	H[1] = H.back();
	H.pop_back();
	if(H.size() > 1) heapifyDown(1);
	x->queueIndex = 0;
	return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
	H.push_back(x);
	heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
	heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
	auto x = H[i];
	while (i > 1 && *x < *H[parent(i)]) {
		set(i, H[parent(i)]);
		i = parent(i);
	}
	set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
	auto x = H[i];
	while (true) {
		unsigned k = leftChild(i);
		if (k >= H.size())
			break;
		if (k+1 < H.size() && *H[k+1] < *H[k])
			++k; // right child of i
		if ( ! (*H[k] < *x) )
			break;
		set(i, H[k]);
		i = k;
	}
	set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
	H[i] = x;
	x->queueIndex = i;
}

#endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */
