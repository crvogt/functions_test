#include "NumberList1.h"
#include <cstddef>
#include <iostream>
using namespace std;

void NumberList1::appendNode(double num){
/*
add a node to the end of a list. Function will
allocte a new ListNode structure, store the val
in num, and append the node to the end of the
list. Pseudo code:
Create a new node
Store data in the new node
If there are no nodes in the list
	Make the new node the first node
Else
	Traverse the list to find the last node
	Add the new node to the end of the list
End if
*/
	//To point to a new node
	ListNode *newNode;
	//To move through the list
	ListNode *nodePtr;

	//Allocate a new node and store num there
	newNode = new ListNode;
	newNode->value = num;
	newNode->next = NULL;

	//If no nodes in list
	//Make a newNode the first node
	if(!head)
		head = newNode;
	else{
		//Otherwise insert newNode at end
		//Initialize nodePtr to head of list
		nodePtr = head;

		//Find the last node in list
		while(nodePtr->next)
			nodePtr = nodePtr->next;

		//Insert newNode as the last node
		nodePtr->next = newNode;
	}
}


void NumberList1::deleteNode(double num){
	//To traverse the list
	ListNode *nodePtr;
	//To point to the previous node
	ListNode *previousNode;

	//If the list is empty do nothing
	if(!head)
		return;

	//Determine if the first node is the one
	if(head->value == num){
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else{
		//Initialize nodePtr to head of list
		nodePtr = head;

		//Skip all nodes whose value member is 
		//not equal to num
		while(nodePtr != NULL && nodePtr->value != num){
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		//If nodePtr is not at the end of the lsit
		//link the previous node to the node after
		//nodePtr, then delete nodePtr
		if(nodePtr){
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

void NumberList1::insertNode(double num){
	/*
	Create a new node
	Store data in the new node
	If there are no nodes in the list
		Make the new node the first node
	Else
		Find the first node whose value is 
		greater than or equal to the new val
		or the end of the list (whichever
		is first)
		Insert the new node before the found 
		node or at the end of the list if no
		such node was found
	End If	
	*/
	//A new node
	ListNode *newNode;
	//To traverse the list
	ListNode *nodePtr;
	//The previous node
	ListNode *previousNode = NULL;

	//Allocate a new node and store num there
	newNode = new ListNode;
	newNode->value = num;

	//If there are no nodes in the list
	//make newNode the first node
	if(!head){
		head = newNode;
		newNode->next = NULL;
	}
	//Otherwise insert newNode
	else{
		//Position nodePtr at the head of list
		nodePtr = head;
		
		//Initialize previousNode to null
		previousNode = NULL;
		
		//Skip all nodes whose val is less 
		//than num
		while(nodePtr != NULL && nodePtr->value < num){
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		//If the new node is to be the 1st
		//in the list insert it before all 
		//other nodes
		if(previousNode == NULL){
			head = newNode;
			newNode->next = nodePtr;
		}
		//Otherwise insert after the
		//previous node
		else{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}	
}

void NumberList1::displayList() const{
	/*
	Pseudo code
	Assign List head to node pointer
	While node pointer is not NULL
		Display the value member of the node
		pointed to by node pointer
		Assign node pointer to its own next member
	End while
	*/

	//To move through the list
	ListNode *nodePtr;

	//Position pointer at head of list
	nodePtr = head;

	//While nodePtr points to a node, 
	//traverse the list
	while(nodePtr){
		//Display the value in this node
		cout << nodePtr->value << endl;

		//move to the next node
		nodePtr = nodePtr->next;
	}
}

//AAAaand the destructor
NumberList1::~NumberList1(){
	cout << "\n\nDESTRUCTOR....\nACTIVATED!!\n";
	ListNode *nodePtr;
	ListNode *nextNode;

	nodePtr = head;

	while(nodePtr != NULL){
		nextNode = nodePtr->next;

		delete nodePtr;

		nodePtr = nextNode;
	}
}
