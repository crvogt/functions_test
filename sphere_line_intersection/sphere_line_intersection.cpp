#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char **argv){
	float length = 0.5;
	float theta = atan(3.125 / 2100);
	cout << "theta " << theta * 180 / M_PI << endl;
	float height = length * tan(theta);	
	cout << "length " << length << " height " << height << endl;

	float aimRadius = 0.2;
	float cx = length;
	float cy = height;
	float cz = 0;

	//Find the intersection of the viewing direction with a 
	//sphere of orientation around the subject
	double vx, vy, vz, px, py, pz, A, B, C, D;
	
	//vx = cos(yaw)*cos(pitch);
	float magnitude = sqrt(height*height + length*length);
	vx = length / magnitude;//sin(yaw)*cos(pitch);
	//vy = sin(yaw)*cos(pitch);
	vy = height / magnitude;//sin(pitch);
	//vz = sin(pitch);
	vz = 0;

	//ROS_INFO_STREAM("vx " << vx << " vy " << vy << " vz " << vz);
	px = 0;
	py = 0;
	pz = 0; 
	A = vx * vx + vy * vy + vz * vz;
	B = 2.0 * (px * vx + py * vy + pz * vz - vx * cx - vy * cy - vz * cz);
	C = px * px - 2 * px * cx + cx * cx + py * py - 2 * py * cy + cy * cy +
		pz * pz - 2 * pz * cz + cz * cz - aimRadius * aimRadius;
	float Dx = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
	cout << "\nDx " << Dx << endl;
	float Dy = (height/length)*((-B + sqrt(B * B + 4 * A * C)) / (2 * A));
	cout << "\nDy " << Dy << endl;

	return 0;
}