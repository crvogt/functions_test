#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "csv_parser.h"
#include "predictor_node_lib.h"
using namespace std;

/***************************************************************************/

void parseFile(vector<autopilotData> &flightVec){

	/*
	Function parses several different files as at the moment
	I have data stored on a per-type basis (ie, compass is
	in a file of its own, as is airspeed, groundspeed, etc)
	*/

	//Define the filename string
	string filename;
	//Values to hold the string brought in
	
	string scompass, sgroundspeed, sairspeed, sgpsX, sgpsY, sgpsZ;
	string spressureInATM, slatitude, slongitude, saltitude, scurrentTime, sjunkString;
	autopilotData flightData;

	int vectorSize;
	//Count number of rows we've gone through
	int rows = 0;

	/*
	...Should turn this into a function... will do later, but at
	least we know it works! :D
	*/

	filename = "compass17_3.csv";
	fstream dataFileCompass(filename.c_str(), ios::in);
		while(dataFileCompass){
			getline(dataFileCompass, scompass);
			flightData.compass = stof(scompass);
			flightVec.push_back(flightData);
		}
	dataFileCompass.close();
	dataFileCompass.clear();

	vectorSize = flightVec.size();

	filename = "airspeed17_3.csv";
	fstream dataFileAirspeed(filename.c_str(), ios::in);
	while(rows < vectorSize){
		getline(dataFileAirspeed, sairspeed);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].airspeed = stof(sairspeed);
		rows++;
	}
	dataFileAirspeed.close();
	dataFileAirspeed.clear();
	rows = 0;
	
	
	filename = "altitude17_3.csv";
	fstream dataFileAltitude;
	dataFileAltitude.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileAltitude, saltitude);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].altitude = stof(saltitude);
		rows++;
	}
	dataFileAltitude.close();
	dataFileAltitude.clear();
	rows = 0;

	filename = "latitude17_3.csv";
	fstream dataFileLatitude;
	dataFileLatitude.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileLatitude, slatitude);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].latitude = stof(slatitude);
		rows++;
	}
	dataFileLatitude.close();
	dataFileLatitude.clear();
	rows = 0;

	filename = "longitude17_3.csv";
	fstream dataFileLongitude;
	dataFileLongitude.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileLongitude, slongitude);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].longitude = stof(slongitude);
		rows++;
	}
	dataFileLongitude.close();
	dataFileLongitude.clear();
	rows = 0;

	filename = "X17_3.csv";
	fstream dataFileX;//(filename.c_str()), ios::in);
	dataFileX.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileX, sgpsX);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].X = stof(sgpsX);
		rows++;
	}
	dataFileX.close();
	dataFileX.clear();
	rows = 0;

	filename = "Y17_3.csv";
	fstream dataFileY;
	dataFileY.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileY, sgpsY);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].Y = stof(sgpsY);
		rows++;
	}
	dataFileY.close();
	dataFileY.clear();
	rows = 0;

	filename = "Z17_3.csv";
	fstream dataFileZ;
	dataFileZ.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileZ, sgpsZ);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].Z = stof(sgpsZ);
		rows++;
	}
	dataFileZ.close();
	dataFileZ.clear();
	rows = 0;

	filename = "pressure17_3.csv";
	fstream dataFilePressure;//(filename.c_str()), ios::in);
	dataFilePressure.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFilePressure, spressureInATM);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].pressureInATM = stof(spressureInATM);
		rows++;
	}
	dataFilePressure.close();
	dataFilePressure.clear();
	rows = 0;

	filename = "groundspeed17_3.csv";
	fstream dataFileGroundspeed;//(filename.c_str()), ios::in);
	dataFileGroundspeed.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileGroundspeed, sgroundspeed);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].groundspeed = stof(sgroundspeed);
		rows++;
	}
	dataFileGroundspeed.close();
	dataFileGroundspeed.clear();
	rows = 0;

	filename = "time17_3.csv";
	fstream dataFileTime;//(filename.c_str()), ios::in);
	dataFileTime.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileTime, scurrentTime);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].currentTime = stof(scurrentTime);
		rows++;
	}
	dataFileTime.close();
	dataFileTime.clear();
	rows = 0;
/*
	for(rows = 0; rows < vectorSize; rows++){
		cout << "ROW " << (rows+1) << endl
			 << "compass " << flightVec[rows].compass
			 << " groundspeed " << flightVec[rows].groundspeed
			 << " airspeed " << flightVec[rows].airspeed << endl << endl
			 << "X " << flightVec[rows].X 
			 << " Y " << flightVec[rows].Y
			 << " Z " << flightVec[rows].Z << endl << endl
			 << "pressure " << flightVec[rows].pressureInATM 
			 << " latitude " << flightVec[rows].latitude
			 << " longitude " << flightVec[rows].longitude << endl << endl
			 << "altitude " << flightVec[rows].altitude
			 << " currentTime " << flightVec[rows].currentTime << endl << endl;
	}
*/
	//return;
}

/**********************************************************************/
/*
void accessFiles(std::vector<autopilotData> &flightVec, std::vector<string> &filenames){
	string sholder;
	if(flightVec.empty(filenames[0].c_str())){
		fstream dataFile.open();
		while
	}
	fstream dataFile;
	dataFileAltitude.open(filename.c_str());
	while(rows < vectorSize){
		getline(dataFileAltitude, saltitude);
		//flightData.airspeed = stof(sairspeed);
		//cout << "\nAirspeed value " << flightData.airspeed << endl;
		flightVec[rows].altitude = stof(saltitude);
		rows++;
	}
	dataFileAltitude.close();
	dataFileAltitude.clear();
	rows = 0;
}
*/
/**********************************************************************/

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

	if(values->smallAlt > 0){
		for(int i = 0; i < size; i++){
			flightVec[i].altitude = flightVec[i].altitude - values->smallAlt;
		}

		//Normalize the altitude values
		values->largeAlt -= values->smallAlt;
		values->smallAlt = 0;
	}

	//print results
	
	cout << "\nThis is the output from the extremes parsing:\n";
	cout << "smallLat " << values->smallLat << endl
		 << "largeLat " << values->largeLat << endl
		 << "smallLong " << values->smallLong << endl
		 << "largeLong " << values->largeLong << endl
		 << "smallAlt " << values->smallAlt << endl
		 << "largeAlt " << values->largeAlt << endl;
	
	return;
}

/*****************************************************************************/

void printToMatlabReadable(vector<ValueBlock *> &cubeVector){
	/*
	Want to write out to a csv file easily read by MATLAB to plot the data
	quiver3(x,y,z,u,v,w)
	u, v, and w are the directional vectors which, when resolved, will be
	scaled automatically with respect to eachother and shown in the finished
	direction (the combination of the three) i j k

	Possible to normalize
	*/
}

