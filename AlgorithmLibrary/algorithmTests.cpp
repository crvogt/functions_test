#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
struct values{
	float a;
	float b;
};
*/
int main(int argc, char **argv){
	vector<int> valueVec;
	float lower, upper;

	valueVec.push_back(4);
//	valueVec[0].b = 6;
	valueVec.push_back(233);
//	valueVec[1].b = 1000;
	valueVec.push_back(22);
//	valueVec[2].b = 9832;

	lower = *min_element(valueVec.begin(), valueVec.begin());

	cout << "\nlower = " << lower << endl;

	return 0;
}
