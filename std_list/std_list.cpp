#include <iostream>
#include <list>

int main(int argc, char **argv){

	std::list<int> first;
	std::list<int> second(4, 100);
	std::list<int> third (second.begin(), second.end());
	std::list<int> fourth(third);

	int myints[] = {16, 2, 77, 29};
	std::list<int> fifth(myints, myints + 3);//sizeof(myints) / sizeof(int));
	std::cout << myints << " " << sizeof(myints) << " " << std::endl;
	std::cout << myints + sizeof(myints) / sizeof(int) << std::endl;
	std::cout << "The contents of fifth are: ";
	for(std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
		std::cout << *it << " ";

	std::cout << "\n";

	return 1;
}