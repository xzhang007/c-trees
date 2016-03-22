#ifndef __NODE_H__
#define __NODE_H__

/*************************************
* Student name Xuan Zhang
* Student ID 916409525
* Email xzhang8@mail.sfsu.edu
* Compiler used to test program (including version) gcc version 4.9.3 (GCC)
*************************************/

template <typename T>
class Node {
  public:
    Node();
    Node( T );
    ~Node();
    
    T data;
    Node<T> * left;
    Node<T> * right;
};

// Implement this
template <typename T>
Node<T>::Node() {
	data = 0;
	left = NULL;
	right = NULL;
}

template <typename T>
Node<T>::Node( T value ) {
	data = value;
	left = NULL;
	right = NULL;
}

template <typename T>
Node<T>::~Node() {
	delete left;
	delete right;
}

#endif