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

void printResults(std::vector<autopilotData> &);

void parseFile(void);


#endif