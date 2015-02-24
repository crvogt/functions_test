#include <iostream>
#include "ros/ros.h"
using namespace std;

#define NUMBER_OF_WAYPOINTS 5

struct Waypoint{
/*
	uint8 FRAME_GLOBAL = 0;
	uint8 FRAME_LOCAL_NED = 1;
	uint8 FRAME_MISSION = 2;
	uint8 FRAME_GLOBAL_REL_ALT = 3;
	uint8 FRAME_LOCAL_ENU = 4;
	uint16 NAV_WAYPOINT = 16;
        uint16 NAV_LOITER_UNLIM = 17;
        uint16 NAV_LOITER_TURNS = 18;
        uint16 NAV_LOITER_TIME = 19;
        uint16 NAV_RETURN_TO_LAUNCH = 20;
        uint16 NAV_LAND = 21;
        uint16 NAV_TAKEOFF = 22;
	uint8 frame;
	uint16 command;
	bool is_current;
	bool autocontinue;
	float32 param1;
	float32 param2;
	float32 param3;
	float32 param4;
	float64 x_lat;
	float64 y_long;
	float64 z_alt;
*/
	static const int FRAME_GLOBAL = 0;
        static const int FRAME_LOCAL_NED = 1;
        static const int FRAME_MISSION = 2;
        static const int FRAME_GLOBAL_REL_ALT = 3;
        static const int FRAME_LOCAL_ENU = 4;
        static const int NAV_WAYPOINT = 16;
        static const int NAV_LOITER_UNLIM = 17;
        static const int NAV_LOITER_TURNS = 18;
        static const int NAV_LOITER_TIME = 19;
        static const int NAV_RETURN_TO_LAUNCH = 20;
        static const int NAV_LAND = 21;
        static const int NAV_TAKEOFF = 22;
        int frame;
        int command;
        bool is_current;
        bool autocontinue;
        float param1;
        float param2;
        float param3;
        float param4;
        double x_lat;
        double y_long;
        double z_alt;
};


int main(int argc, char **argv){
	//Trying to make an array of waypoints
	Waypoint waypointArray[NUMBER_OF_WAYPOINTS];

	return 0;
}	
