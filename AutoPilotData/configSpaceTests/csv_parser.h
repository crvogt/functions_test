#ifndef __CSV_PARSER_H
#define __CSV_PARSER_H

#include <vector>
#include <iostream>

#define COLUMNS 21

struct autopilotData{
	float compass; 			//column 1/0
	float groundspeed;  	//column 4/3
	float airspeed; 		//column 2/1
	double X; 				//column 11/10
	double Y;				//column 12/11
	double Z;				//column 13/12
	double pressureInATM;	//column 20/19
	double latitude;		//column 8/7
	double longitude;		//column 9/8
	float altitude;			//column 10/9
	double currentTime; 	//column 21/20  
};

struct extremes{
	double smallLat;
	double largeLat;
	double smallLong;
	double largeLong;
	double smallAlt;
	double largeAlt;
};

void printResults(std::vector<autopilotData> &);

//An int value to declare which extreme we're looking for
//ie, large/small long, large/small lat, large/small alt
void returnExtremes(std::vector<autopilotData> &, extremes *);

void parseFile(std::vector<autopilotData> &);


#endif