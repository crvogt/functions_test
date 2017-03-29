#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv){
	//create grid over entire sphere
	//float radius = 1.0;
	bool CGALFormat = true;
	bool withNormals = true;
	float magnitude;
	Point3f tempLoc;
	Point3f tempOrient;
	Point3f sphereCenter(0, 0, 0);
	vector<Point3f> locations;
	vector<Point3f> orientations;
	ofstream pointsOut;
	pointsOut.open("/home/carson/opencv_proj/cgal/spherical_surface_mesh/data/sphere.xyz");

	for(int phi = 0; phi < 180;){
		for(int theta = 0; theta < 360;){
			tempLoc.x = cos(theta * 180 / M_PI) * sin(phi * 180 / M_PI);
			tempLoc.y = sin(theta * 180 / M_PI) * sin(phi * 180 / M_PI);
			tempLoc.z = cos(phi * 180 / M_PI);

			//assign basic values
			tempOrient.x = sphereCenter.x - tempLoc.x;
			tempOrient.y = sphereCenter.y - tempLoc.y;
			tempOrient.z = sphereCenter.z - tempLoc.z;
			//cout<<"tempOrientxf "<<tempOrient.x<<" tempOrientyf "<<tempOrient.y<<" tempOrientzf "<<tempOrient.z<<endl;

			//now normalize
			magnitude = sqrt(tempOrient.x*tempOrient.x + tempOrient.y*tempOrient.y + tempOrient.z*tempOrient.z);
			tempOrient.x = tempOrient.x / magnitude;
			tempOrient.y = tempOrient.y / magnitude;
			tempOrient.z = tempOrient.z /  magnitude;
			//cout<<"tempOrientx "<<tempOrient.x<<" tempOrienty "<<tempOrient.y<<" tempOrientz "<<tempOrient.z<<endl;

			locations.push_back(tempLoc);
			orientations.push_back(tempOrient);
			phi += 1;
			theta += 1;
		}
	}

	if(!CGALFormat){
		for(int i = 0; i < locations.size(); i++){
			pointsOut << locations[i].x << "\n";
			pointsOut << locations[i].y << "\n";
			if(i < locations.size() - 1){
				pointsOut << locations[i].z << "\n";
			}
			else{
				pointsOut << locations[i].z;
			}
		}
	}
	else if(CGALFormat && withNormals){
		for(int i = 0; i < locations.size(); i++){
			pointsOut << locations[i].x << " " << locations[i].y << " " 
				<< locations[i].z << " " << orientations[i].x << " " 
				<< orientations[i].y << " ";
			if(i < locations.size() - 1){
				pointsOut << orientations[i].z << "\n";
			}
			else{
				pointsOut << orientations[i].z;
			}
				
		}
	}
	else{
		for(int i = 0; i < locations.size(); i++){
			pointsOut << locations[i].x << " " << locations[i].y << " ";
			if(i < locations.size() - 1){
				pointsOut << locations[i].z << "\n";
			}
			else{
				pointsOut << locations[i].z;
			}		
		}	
	}

	return 0;
}