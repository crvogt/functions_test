#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "csv_parser.h"
using namespace std;

void parseFile(void){
	//Define the vector
	vector<autopilotData> flightVec;

	//Define the filename string
	string filename;
	string scompass, sgroundspeed, sairspeed;
	autopilotData flightData;
	filename = "csvTest.csv";

	fstream dataFile(filename.c_str(), ios::in);

	//counter to skip data we don't want
	int counter = 0;

	//if the file opened, continue
	if(dataFile){
		getline(dataFile, scompass, ',');
		flightData.compass = stof(scompass);
		//cout << "Extracted value: " << flightData.compass << endl;
		//cout << "Modified extracted value (x2): " << (flightData.compass * 2) << endl;
		counter++;

		//while lsat read successful, continue
		cout << "\nJust before entering loop, value of counter: " << counter;
		while(dataFile){
			cout << "\nJust inside loop";
			switch(counter){
				case 0:
					getline(dataFile, scompass, ',');
					flightData.compass = stof(scompass);
					break;
				case 1:
					getline(dataFile, sgroundspeed, ',');
					flightData.groundspeed = stof(sgroundspeed);
					break;
				case 2:
					getline(dataFile, sairspeed, ',');
					flightData.airspeed = stof(sairspeed);
					break;
			}
			counter++;

			if(counter > (COLUMNS - 1)){
				flightVec.push_back(flightData);
				counter = 0;
				cout << "\nInside if statement";
			}
		}

		//Print the results
		printResults(flightVec);

		dataFile.close();
	}
}

void printResults(vector<autopilotData> &flightVec){
	cout << "\nFirst value: " <<flightVec[0].compass << endl;
}