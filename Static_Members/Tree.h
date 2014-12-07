//Tree class 
#ifndef TREE_H
#define TREE_H

class Tree{
private:
	static int objectCount; //static mem variable

public:
	//Constructor
	Tree(){
		objectCount++;
	}

	//Accessor function for objectCount
	int getObjectCount() const{
		return objectCount;
	}

};

//Definition of the static member variable, written
//outisde the class

int Tree::objectCount = 0;

#endif