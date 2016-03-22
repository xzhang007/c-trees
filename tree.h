#ifndef __TREE_H__
#define __TREE_H__

// tree.h
#include "node.h"
#include <iostream>
#include <stdexcept>
/*************************************
* Student name Xuan Zhang
* Student ID 916409525
* Email xzhang8@mail.sfsu.edu
* Compiler used to test program (including version) gcc version 4.9.3 (GCC)
*************************************/

template <typename T>
class Tree {
public:
	Tree();
	~Tree();
	void insert(T);
	bool contains(T);
	void remove(T);
	bool isFull();
	int height();
	void preorder();
	void inorder();
	void postorder();

	bool isEmpty();

private:
	int height(Node<T> *);
	bool isFull(Node<T> *);
	void preorder(Node<T> *);
	void inorder(Node<T> *);
	void postorder(Node<T> *);

	Node<T> * root;
};

template <typename T>
Tree<T>::Tree() {
	root = NULL;
}

template <typename T>
Tree<T>::~Tree() {
	delete root;
}

template <typename T>
void Tree<T>::insert(T value) {
	Node<T> * newNode = new Node<T>(value);
	Node<T> * parentNode = NULL;

	if (root == NULL) {
		root = newNode;
		return;
	}

	Node<T> * currentNode = root;
	while (currentNode) {
		parentNode = currentNode;
		currentNode = newNode->data > currentNode->data ? currentNode->right : currentNode->left;
	}

	if (newNode->data > parentNode->data)
		parentNode->right = newNode;
	else 
		parentNode->left = newNode;
}

template <typename T>
bool Tree<T>::contains(T value) {
	if (root == NULL)
		return false;

	Node<T> * currentNode = root;
	while (currentNode) {
		if (currentNode->data == value)
			return true;
		else 
			currentNode = currentNode->data > value ? currentNode->left : currentNode->right;
	}

	return false;
}

template <typename T>
void Tree<T>::remove(T value) {
	if (root == NULL)
		throw std::runtime_error("Invalid Action!");

	Node<T> * currentNode = root;
	Node<T> * parentNode = NULL;

	while (currentNode) {
		if (currentNode->data == value)
			break;
		else {
			parentNode = currentNode;
			currentNode = value > currentNode->data ? currentNode->right : currentNode->left;
		}
	}

	if (currentNode == NULL) {
		std::cout << "key not found!" << std::endl;
		return;
	}
	
	if (currentNode->left == NULL && currentNode->right == NULL) {	// currentNode is a leaf
		if (currentNode == root) 
			root = NULL;
		else if (parentNode->left == currentNode)
			parentNode->left = NULL;
		else
			parentNode->right = NULL;
	} else if (currentNode->left != NULL && currentNode->right == NULL) {	// currentNode has only one child
		if (currentNode == root) 
			root = currentNode->left;

		if (parentNode->left == currentNode) 
			parentNode->left = currentNode->left;
		else 
			parentNode->right = currentNode->left;

		currentNode->left = NULL;	// This is very important!
	} else if (currentNode->left == NULL && currentNode->right != NULL) {	// currentNode has only one child
		if (currentNode == root)
			root = currentNode->right;

		if (parentNode->left == currentNode)
			parentNode->left = currentNode->right;
		else 
			parentNode->right = currentNode->right;
		
		currentNode->right = NULL;	// This is very important!
	} else if (currentNode->left != NULL && currentNode->right != NULL) {	// currentNode has two children
		Node<T> * successor = currentNode->right;
		Node<T> * parentOfSuccessor = NULL;
		while (successor->left) {
			parentOfSuccessor = successor;
			successor = successor->left;
		}

		if (currentNode == root) 
			root = successor;

		if (parentNode->left == currentNode) 
			parentNode->left = successor;
		else 
			parentNode->right = successor;
			
		successor->left = currentNode->left;
		if (successor != currentNode->right)
			successor->right = currentNode->right;

		currentNode->left = NULL;	// This is very important!
		currentNode->right = NULL;	// This is very important!

		if (parentOfSuccessor)
				parentOfSuccessor->left = NULL;
	}

	// currentNode->left = NULL;
	// currentNode->right = NULL;
	delete currentNode;
}

template <typename T>
bool Tree<T>::isFull() {
	return isFull(root);
}

template <typename T>
bool Tree<T>::isFull(Node<T> * node) {
	if (node == NULL)
		return true;
	else if ((node->left == NULL && node->right != NULL) || (node->left != NULL && node->right == NULL)) 
		return false;
	else if (node->left == NULL && node->right == NULL)
		return true;

	return isFull(node->left) && isFull(node->right);
}

template <typename T>
int Tree<T>::height() {
	return height(root);
}

template <typename T>
void Tree<T>::preorder() {
	preorder(root);
}

template <typename T>
void Tree<T>::preorder(Node<T> * node) {
	if (node != NULL) {
		std::cout << node->data << std::endl;
		preorder(node->left);
		preorder(node->right);
	}
}

template <typename T>
void Tree<T>::inorder() {
	inorder(root);
}

template <typename T>
void Tree<T>::inorder(Node<T> * node) {
	if (node != NULL) {
		inorder(node->left);
		std::cout << node->data << std::endl;
		inorder(node->right);
	}
}

template <typename T>
void Tree<T>::postorder() {
	postorder(root);
}

template <typename T>
void Tree<T>::postorder(Node<T> * node) {
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		std::cout << node->data << std::endl;
	}
}

template <typename T>
bool Tree<T>::isEmpty() {
	return root == NULL;
}

template <typename T>
int Tree<T>::height(Node<T> * node) {
	if (node == NULL)
		return 0;

	return 1+ std::max(height(node->left), height(node->right));
}

#endif