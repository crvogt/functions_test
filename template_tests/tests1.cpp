#include <iostream>

using namespace std;

template <class myType>
myType GetMax(myType a, myType b){
	return(a>b?a:b);
}

int main(int argc, char **argv){

	int l = 3, b = 4, m;
	float k = 4.0, d = 4.2, f;

	f = GetMax<float>(k, d);
	m = GetMax<int>(l, b);

	cout << endl << f << endl;
	cout << endl << m << endl;

	return 1;
}
