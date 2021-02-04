/******************************************************
* Program: Linked_List.hpp
* Author: Cameron McCawley
* Date: 12/06/2019
* Description: Declares and implements the Linked List
*	template class.
******************************************************/

#pragma once
#include <iostream>
#include <cstdlib>
#include "Node.hpp"
using namespace std;

template <class T>
class Linked_List{
	public:
		Linked_List<T>();
		~Linked_List();

		int get_length();
		void print();
		void clear();
		unsigned int push_back(T const &data);
		unsigned int push_front(T const &data);
		unsigned int insert(T const &data, int index);
		void sort_ascending();
		void sort_descending();
		int get_num_primes();

	private:
		Node<T>* sorted_merge(Node<T>*, Node<T>*, bool);
		void split(Node<T>*, Node<T>**, Node<T>**);
		void merge_sort(Node<T>**, bool);
		unsigned int length;
		Node<T> *head;
		Node<T> *tail;
		T power(T, unsigned int, int);
		bool miller_test(T, T);
		bool is_prime(T, int);
};

//Implementation

/******************************************************
* Function: Linked_List
* Parameters: none 
* Descriptiion: Initializes the Linked_List member variables
******************************************************/
template <class T>
Linked_List<T>::Linked_List(){
	head = nullptr;
	tail = nullptr;
	length = 0;	
}

/******************************************************
* Function: ~Linked_List
* Parameters: none
* Description: Calls the clear function when linked 
*	list is destroyed
******************************************************/
template <class T>
Linked_List<T>::~Linked_List(){
	clear();
}

/******************************************************
* Function: clear
* Parameters: none
* Description: Deletes the allocated memory used for
*	the linked list.  Also gets rid of any dangling
*	pointers
******************************************************/
template <class T>
void Linked_List<T>::clear(){
	Node<T> *curr = head;
	while(curr != nullptr){
		Node<T> *next = curr->next;
		curr->next = nullptr;
		delete curr;
		curr = next;
		next = nullptr;
	}
}

/******************************************************
* Function: get_length
* Parameters: none
* Returns: int
* Description: returns the length of the linked list
******************************************************/
template <class T>
int Linked_List<T>::get_length(){
	return length;
}

/******************************************************
* Function: print
* Parameters: none
* Returns: void
* Description: Prints the contents of the linked list
******************************************************/
template <class T>
void Linked_List<T>::print(){
	Node<T> *temp = head;
	while(temp != nullptr){
		cout << temp->val << " ";
		temp = temp->next;
	}		
	cout << endl;
}

/******************************************************
* Function:	push_back
* Parameters: const T &
* Returns: unsigned int
* Description: Appends a node to the end of the linked 
*	list containing the data passed in
******************************************************/
template <class T>
unsigned int Linked_List<T>::push_back(const T &data){
	auto *new_node = new Node<T>(data);

	if(length == 0){
		head = new_node;
		tail = new_node;
		length = 1;
	}else{
		tail->next = new_node;
		tail = new_node;
		length++;
	}
	
	new_node = nullptr;
	return length;
}

/******************************************************
* Function: push_front
* Parameters: const T &
* Returns: unsigned int
* Description: pushes a node to the front of the list
******************************************************/
template <class T>
unsigned int Linked_List<T>::push_front(const T &data){
	auto *new_node = new Node<T>(data);

	if(length == 0){
		head = new_node;
		tail = new_node;
		length = 1;
		new_node = nullptr;
	}else{
		new_node->next = head;
		head = new_node;
		length++;
	}
	
	return length;
}

/******************************************************
* Function: insert
* Parameters: const T &, int
* Returns: unsigned int
* Description: Inserts a node at the index specified in
*	the list. Index cannot be out of bounds.
******************************************************/
template <class T>
unsigned int Linked_List<T>::insert(const T &data, int index){

	if(length == index){
		return this->push_back(data);
	}else if(index == 0){
		return this->push_front(data);
	}else{
		auto *new_node = new Node<T>(data);
		Node<T> *curr = head;		

		for(int i = 0; i < index - 1; i++){
			curr = curr->next;
		}

		new_node->next = curr->next;
		curr->next = new_node;
		length++;
		new_node = nullptr;
		return length;
	}
}

/******************************************************
* Function: sort_ascending
* Parameters: none
* Returns: void
* Description: Calls the merge_sort function with the 
*	ascending flag
******************************************************/
template <class T>
void Linked_List<T>::sort_ascending(){
	merge_sort(&head, true);
}

/******************************************************
* Function: sort_descending
* Parameters: none
* Returns: void
* Description: calls the merge_sort function with the 
*	descending flag
******************************************************/
template <class T>
void Linked_List<T>::sort_descending(){
	merge_sort(&head, false);
}

/******************************************************
* Function: merge_sort
* Parameters: Node<T>**, bool
* Returns: void
* Description: Resursive merge-sort algorithm 
******************************************************/
template <class T>
void Linked_List<T>::merge_sort(Node<T>** start_head, bool ascend){
	Node<T>* head = *start_head;
	Node<T>* a;
	Node<T>* b;

	if((head == nullptr) || (head->next == nullptr)){
		return;
	}

	split(head, &a, &b); //split list in half

	merge_sort(&a, ascend); //Recursie merge
	merge_sort(&b, ascend);

	*start_head = sorted_merge(a, b, ascend);
}

/******************************************************
* Function: sorted_merge
* Parameters: Node<T>*, Node<T>*, bool
* Returns: Node<T>*
* Description: Merges two linked lists together into 
*	one linked list in either ascending or descending
*	order.
******************************************************/
template <class T>
Node<T> * Linked_List<T>::sorted_merge(Node<T>* a, Node<T>* b, bool ascend){
	Node<T>* result = nullptr;

	if(a == nullptr){
		return b;
	}else if(b == nullptr){
		return a;
	}
	
	if(ascend ? a->val <= b->val : a->val >= b->val){
		result = a;
		result->next = sorted_merge(a->next, b, ascend);

	}else{
		result = b;
		result->next = sorted_merge(a, b->next, ascend);
	}
	return result;
}

/******************************************************
* Function: split
* Parameters: Node<T>*, Node<T>**, Node<T>**
* Returns: void
* Description: Splits the linked list in half
******************************************************/
template <class T>
void Linked_List<T>::split(Node<T>* source, Node<T>** front, Node<T>** back){
	Node<T>* fast; //Fast will iterate the list by two
	Node<T>* slow; //Slow will iterate by one
	slow = source;
	fast = source->next;

	while(fast != nullptr){
		fast = fast->next;
		if(fast != nullptr){
			slow = slow->next;
			fast = fast->next;
		}
	}

	*front = source;
	*back = slow->next;
	slow->next = nullptr;
}

/******************************************************
* Function: power
* Parameters: T, unsigned int, int
* Returns: t
* Description: utility function for modular exponentiation.
*	Calculates and returns (x^y) % p
******************************************************/
template <class T>
T Linked_List<T>::power(T x, unsigned int y, int p){
	T res = 1;
	x = x % p;
	while(y > 0){
		if(y & 1){
			res = (res*x) % p;
		}
		//y must be even now
		y /= 2;
		x = (x*x) % p;
	}
	return res;
}

/******************************************************
* Function: miller_test
* Parameters: T, T
* Returns: bool
* Description: Runs the Miller_Rabin Primality test
*	algorithm
******************************************************/
template <class T>
bool Linked_List<T>::miller_test(T d, T n){
	T a = 2 + rand() % (n - 4);
	T x = power(a, d, n);

	if(x == 1 || x == n - 1){
		return true;
	}
	while(d != n - 1){
		x = (x * x) %  n;
		d *= 2;
		if(x == 1)
			return false;
		if(x == n - 1)
			return true;
	}

	return false;
}

/******************************************************
* Function: is_prime
* Parameters: T, int
* Returns: bool
* Description: Returns true if n is probably prime, false
*	if it is not
******************************************************/
template <class T>
bool Linked_List<T>::is_prime(T n, int k){
	if(n <= 1 || n == 4)
		return false;

	if(n <= 3)
		return true;
	
	T d = n - 1;
	while(d % 2 == 0)
		d /= 2;

	for(int i = 0; i < k; i++)
		if(!miller_test(d, n))
			return false;

	return true;
}

/******************************************************
* Function: get_num_primes
* Parameters: none
* Returns: int
* Description: Gets the number of prime numbers in the 
*	linked list
******************************************************/
template <class T>
int Linked_List<T>::get_num_primes(){
	int num_primes = 0;
	int k = 15;
	Node<T>* temp = head;
	while(temp != nullptr){

		if(is_prime(temp->val, k)){
			num_primes++;
		}
		temp = temp->next;
	}
	return num_primes;
}

