#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

#include "csv_parser.h"
#include "predictor_node_lib.h"

using namespace std;


int main(int argc, char **argv){
	
	//Define the vector
	vector<autopilotData> flightVec;
	parseFile(flightVec);
	//checkCube(flightVec);

	//extremes test
	extremes values;
	returnExtremes(flightVec, &values);
	cout << "\nThis is the output from the extremes parsing:\n";
		cout << "smallLat " << values.smallLat << endl
			 << "largeLat " << values.largeLat << endl
			 << "smallLong " << values.smallLong << endl
			 << "largeLong " << values.largeLong << endl
			 << "smallAlt " << values.smallAlt << endl
			 << "largeAlt " << values.largeAlt << endl;

	return 0;
}

