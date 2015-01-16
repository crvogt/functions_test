#include "IntBinaryTree1.h"
#include <iostream>
using namespace std;
/*
Code to inerst a node into the tree
Public member function insertNode is called
with the number to be inserted passed as an
argument.
my love electronic
*/

/*********************************
private
*********************************/
void IntBinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode){
	if(nodePtr == NULL) 
		nodePtr = newNode; //insert the node
	else if(newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode); //search left branch
	else
		insert(nodePtr->right, newNode); //search right branch
}

void IntBinaryTree::displayInOrder(TreeNode *nodePtr) const{
	/*******************************
	Displays the values in the subtree pointed
	to by nodePtr, via inorder traversal
	*******************************/
	if(nodePtr){
		displayInOrder(nodePtr->left);
		cout << nodePtr->value << endl;
		displayInOrder(nodePtr->right);
	}
}

void IntBinaryTree::displayPreOrder(TreeNode *nodePtr) const{
	if(nodePtr){
		cout << nodePtr->value << endl;
		displayPreOrder(nodePtr->left);
		displayPreOrder(nodePtr->right);
	}
}

void IntBinaryTree::displayPostOrder(TreeNode *nodePtr) const{
	if(nodePtr){
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		cout << nodePtr->value << endl;
	}
}

void IntBinaryTree::makeDeletion(TreeNode *&nodePtr){
	/*
	This node deletion works a little bit 
	differently from how you might do it.
	Rather than deleting the child nodes,
	it deletes a node then attaches a child
	node to the parent, then the other child
	node becomes child to the child...
	Feel free to change 
	*/

	//Define a temporary pointer to use
	//in reattaching the left subtree
	TreeNode *tempNodePtr;

	if(nodePtr == NULL){
		cout << "\nCannot delete empty node\n";
	}
	else if(nodePtr->right == NULL){
		tempNodePtr = nodePtr;
		//Reattach the left child
		nodePtr = nodePtr->left;
		delete tempNodePtr;
	}
	else if(nodePtr->left == NULL){
		tempNodePtr = nodePtr;
		//Reaatach the right child
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
	//if the node has two children
	else{
		//Move one node to the right
		tempNodePtr = nodePtr->right;
		//Go to the end left node
		while(tempNodePtr->left){
			tempNodePtr = tempNodePtr->left;
		}
		//Reattach the left subtree
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		//Reattach the right subtree
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

void IntBinaryTree::deleteNode(int num, TreeNode *&nodePtr){
	if(num < nodePtr->value)
		deleteNode(num, nodePtr->left);
	else if(num > nodePtr->value)
		deleteNode(num, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

void IntBinaryTree::destroySubTree(TreeNode *nodePtr){
	if(nodePtr){
		if(nodePtr->left){
			destroySubTree(nodePtr->left);
		}
		if(nodePtr->right){
			destroySubTree(nodePtr->right);
		}
		delete nodePtr;
	}
}

/*********************************
public
*********************************/

void IntBinaryTree::remove(int num){
	//Yeah, it's weird
	deleteNode(num, root);
}

void IntBinaryTree::insertNode(int num){
	//Pointer to a new node
	TreeNode *newNode;

	//Create a new node and store num in it
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = NULL;

	//Insert the node
	insert(root, newNode);
}

bool IntBinaryTree::searchNode(int num){
	TreeNode *nodePtr = root;

	while(nodePtr){
		if(nodePtr->value == num){
			return true;
		}
		else if(num < nodePtr->value){
			nodePtr = nodePtr->left;
		}
		else{
			nodePtr = nodePtr->right;
		}
	}
		
		return false;
}