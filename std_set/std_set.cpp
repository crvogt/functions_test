#include <iostream>
#include <set>

bool fncomp(int lhs, int rhs){
	return lhs < rhs;
}

struct classcomp{
	bool operator()(const int &lhs, const int &rhs) const{
		return lhs < rhs;
	}
};

int main(int argc, char **argv){

	std::set<int> first;			//empty set of ints

	int myints[] = {10, 20, 30, 40, 50};
	std::set<int> second(myints, myints+5);

	std::set<int> third(second);	//A copy of second
	std::set<int> fourth(second.begin(), second.end()); //iterator ctor
	std::set<int, classcomp> fifth;	//class as Compare

	bool(*fn_pt)(int, int) = fncomp;
	std::set<int, bool(*)(int, int) > sixth(fn_pt); 	//function ptr as compare

	return 1;
}