#include <iostream>

class Animal{
public:
	virtual void eat(){std::cout << "I eat grass" << std::endl;}
};

class Cat : public Animal{
public:
	// void eat(){std::cout << "I eat mice" << std::endl;}
};

int main(int argc, char **argv){

	Animal *genAnimal = new Animal;
	Cat *regCat = new Cat;

	genAnimal->eat();
	regCat->eat();

	return 0;
}