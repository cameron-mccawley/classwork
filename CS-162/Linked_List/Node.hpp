/******************************************************
* Program: Node.hpp
* Author: Cameron McCawley
* Date: 12/06/2019
* Description: Declares and implements the Node template
*	class
******************************************************/
#pragma once

template <class T>
class Node{
	public:
		Node();
		Node(const T &data);
		~Node();

		T val;
		Node<T> *next;
};

//Implementation

/******************************************************
* Function: Node
* Parameters: none 
* Description: Node default constructor.  Just calls the 
*	parameterized constructor with nullptr
******************************************************/
template <class T>
Node<T>::Node() : Node::Node(nullptr){
}

/******************************************************
* Function: Node
* Parameters: const T &
* Description: Node parameterized constructor.
******************************************************/
template <class T>
Node<T>::Node(const T &data){
	next = nullptr;
	val = data;
}

/******************************************************
* Function: ~Node
* Parameters: none 
* Description: Called on deletion of Node
******************************************************/
template <class T>
Node<T>::~Node(){
	next = nullptr;
}

