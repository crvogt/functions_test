#ifndef INTBINARYTREE1_H
#define INTBINARYTREE1_H
#include <cstddef>
//cstddef is required for NULL

class IntBinaryTree{
private:
	struct TreeNode{
		//The value in the node
		int value;
		//Pointer to left child node
		TreeNode *left;
		//Pointer to right child node
		TreeNode *right;
	};
	TreeNode *root;

	//Private member functions
	void insert(TreeNode *&, TreeNode *&);
	void destroySubTree(TreeNode *);
	void deleteNode(int, TreeNode *&);
	void makeDeletion(TreeNode *&);
	void displayInOrder(TreeNode *) const;
	void displayPreOrder(TreeNode *) const;
	void displayPostOrder(TreeNode *) const;

public:
	//constructor
	IntBinaryTree(){
		root = NULL;
	}

	//Destructor
	~IntBinaryTree(){
		destroySubTree(root);
	}

	//Binary tree operations
	void insertNode(int);
	bool searchNode(int);
	void remove(int);
	
	void displayInOrder() const{
		displayInOrder(root);
	}
	
	void displayPreOrder() const{
		displayPreOrder(root);
	}

	void displayPostOrder() const{
		displayPostOrder(root);
	}
	
};

#endif