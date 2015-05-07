#ifndef __CSV_PARSER_H
#define __CSV_PARSER_H

#include <vector>
#include <iostream>

#define COLUMNS 3

struct autopilotData{
	float compass;
	float groundspeed;
	float airspeed;
	double X;
	double Y;
	double Z;
	double pressureInATM;
	double latitude;
	double longitude;
	float altitude;
	double currentTime; 
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
double returnExtremes(std::vector<autopilotData> &, int);

void parseFile(void);


#endif