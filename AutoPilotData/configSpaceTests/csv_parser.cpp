#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "csv_parser.h"
using namespace std;

/***************************************************************************/

void parseFile(vector<autopilotData> &flightVec){

	//Define the filename string
	string filename;
	string scompass, sgroundspeed, sairspeed, sgpsX, sgpsY, sgpsZ;
	string spressureInATM, slatitude, slongitude, saltitude, scurrentTime, sjunkString;
	autopilotData flightData;
	filename = "Roslin_Third_Flight_March_17.csv";

	fstream dataFile(filename.c_str(), ios::in);

	//counter to skip data we don't want
	int counter = 0;
	int rows = 0;

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
			switch(counter){
				case 0:
					getline(dataFile, scompass, ',');
					flightData.compass = stof(scompass);
					cout << "\ncase 0\n";
					break;
				case 1:
					getline(dataFile, sairspeed, ',');
					flightData.airspeed = stof(sairspeed);
					cout << "\ncase 1\n";
					break;
				case 3:
					getline(dataFile, sgroundspeed, ',');
					flightData.groundspeed = stof(sgroundspeed);
					cout << "\ncase 3\n";
					break;
				case 7:
					getline(dataFile, slatitude, ',');
					flightData.latitude = stof(slatitude);
					cout << "\ncase 7\n";
					break;	
				case 8:
					getline(dataFile, slongitude, ',');
					flightData.longitude = stof(slongitude);
					cout << "\ncase 8\n";
					break;
				case 9:
					getline(dataFile, saltitude, ',');
					flightData.altitude = stof(saltitude);
					cout << "\ncase 9\n";
					break;
				case 10:
					getline(dataFile, sgpsX, ',');
					flightData.X = stof(sgpsX);
					cout << "\ncase 10\n";
					break;
				case 11:
					getline(dataFile, sgpsY, ',');
					flightData.Y = stof(sgpsY);
					cout << "\ncase 11\n";
					break;
				case 12:
					getline(dataFile, sgpsZ, ',');
					flightData.Z = stof(sgpsZ);
					cout << "\ncase 12\n";
					break;
				case 19:
					getline(dataFile, spressureInATM, ',');
					flightData.pressureInATM = stof(spressureInATM);
					cout << "\ncase 19\n";
					break;
				case 20:
					getline(dataFile, scurrentTime, ',');
					flightData.currentTime = stof(scurrentTime);
					cout << "\ncase 20\n";
					break;
				default:
					getline(dataFile, sjunkString, ',');
					cout << "\nDefault\n";
			}
			cout << "\nValue of counter: " << counter << endl;
			counter++;

			if(counter > (COLUMNS - 1)){
				flightVec.push_back(flightData);
				counter = 0;
				rows++;
				cout << "\nNumber of rows gone through: " << rows << endl;
				//cout << "\nInside if statement";
			}
		}
		dataFile.close();
	}
}

/**********************************************************************/

void printResults(vector<autopilotData> &flightVec){
	cout << "\nFirst value: " <<flightVec[0].compass << endl;
}

/***********************************************************************/

void returnExtremes(vector<autopilotData> &flightVec, extremes *values){
	double tempLat, tempLong, tempAlt;
	int size = flightVec.size();
	int halfSize = size/2;
	//Initialize
	values->smallLat = flightVec[halfSize].latitude;
	values->largeLat = flightVec[halfSize].latitude;
	values->smallLong = flightVec[halfSize].longitude;
	values->largeLong = flightVec[halfSize].longitude;
	values->smallAlt = flightVec[halfSize].altitude;
	values->largeAlt = flightVec[halfSize].altitude;
	for(int i = 0; i < size; i++){
		
		//Sort values by size	
		if(flightVec[i].latitude < values->smallLat)
			values->smallLat = flightVec[i].latitude;
		else if(flightVec[i].latitude >= values->largeLat)
			values->largeLat = flightVec[i].latitude;

		if(flightVec[i].longitude < values->smallLong)
			values->smallLong = flightVec[i].longitude;
		else if(flightVec[i].longitude >= values->largeLong)
			values->largeLong = flightVec[i].longitude;

		if(flightVec[i].altitude < values->smallAlt)
			values->smallAlt = flightVec[i].altitude;
		else if(flightVec[i].altitude >= values->largeAlt)
			values->largeAlt = flightVec[i].altitude;
	}
}





















