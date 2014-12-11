//Specification file for the Numberlist class 
#ifndef NUMBERLIST1_H
#define NUMBERLIST1_H
#include <cstddef>
class NumberList1{
private:
	//Declare a structure for the list
	struct ListNode{
		//The value in this node
		double value;
		//To point to the next node
		struct ListNode *next;
	};
	//List head pointer
	ListNode *head;

public:
	//Constructor
	NumberList1(){
		head = NULL;
	}
	//Destructor
	~NumberList1();

	//Linked list operations
	void appendNode(double);
	void insertNode(double);
	//void deleteNode(double);
	void displayList() const;
};

#endif