#include <iostream>
#include <fstream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char **argv){

	std::ifstream baxFile;
	std::string line;
	std::string fileName = "/media/carson/WDPassport/iccp/test_3_trim_v2/Trimpr2VSphere1.txt";
    int counter = 1;
    float x, y, z, theta, phi, sphereRad = 0.4;
    float zMin = 1000, zMax = -1000;
    float yMin = 1000, yMax = -1000;
    float xMin = 1000, xMax = -1000;
    std::vector<cv::Point3f> imageLocations;
    std::vector<cv::Point3f> realValues;
    std::vector<cv::Mat> allImages;

    baxFile.open(fileName);

	if(baxFile.is_open()){
        while(getline(baxFile, line)){   
            switch(counter){
                case 1: x = stof(line); //Uncomment if 3D
                        counter++;
                        break;
                case 2: y = stof(line);
                        counter++;
                        break;
                case 3: z = stof(line);
                        counter = 1;
                        imageLocations.push_back(cv::Point3f(x, y, z));
                        break;
                default:
                        std::cout << "\nNo Match\n";
            }
        }

        // Find max/min values
        for(int i = 0; i < imageLocations.size(); i++){
            if(imageLocations[i].z < zMin){
                zMin = imageLocations[i].z;
            }
            if(imageLocations[i].z > zMax){
                zMax = imageLocations[i].z;
            }
            if(imageLocations[i].y < yMin){
                yMin = imageLocations[i].y;
            }
            if(imageLocations[i].y > yMax){
                yMax = imageLocations[i].y;
            }
            if(imageLocations[i].x < xMin){
                xMin = imageLocations[i].x;
            }
             if(imageLocations[i].x > xMax){
                xMax = imageLocations[i].x;
            }
        }
    }
 
 	// Shift z down
    for(int it = 0; it < imageLocations.size(); it++){
        if(zMin <= 0)
            imageLocations[it].z += std::abs(zMin);
        else
            imageLocations[it].z -= std::abs(zMin);
    }

    // Now to try some shit
    /****************************************/
    // Shift to correct position
    for(int it = 0; it < imageLocations.size(); it++){
        // y shifted to positive
        if(yMin <= 0)
            imageLocations[it].y += std::abs(yMin);
        else
            imageLocations[it].y -= std::abs(yMin);
        // x shifted to negative
        if(xMax >= 0)
            imageLocations[it].x -= std::abs(xMax);
        else
            imageLocations[it].x += std::abs(xMax);
    }

    yMax = -1000;
    yMin = 1000;
    // Find yMax and shift so origin is in center
    for(int i = 0; i < imageLocations.size(); i++){
        if(imageLocations[i].y < yMin){
            yMin = imageLocations[i].y;
        }
        if(imageLocations[i].y > yMax){
            yMax = imageLocations[i].y;
        }
    }

    // Now shift y by half;
    for(int i = 0; i < imageLocations.size(); i++){
    	imageLocations[i].y -= yMax/2;
    }










    /*******************************************/

    for(int i = 0; i < imageLocations.size(); i++){
        realValues.push_back(imageLocations[i]);
        theta = std::atan(imageLocations[i].y / imageLocations[i].x);
        // std::cout << "sphereRad: " << sphereRad << " y: " << imageLocations[i].y << " x: " << imageLocations[i].x << " y/x: " << imageLocations[i].y/imageLocations[i].x << " theta: " << theta << std::endl;
        phi = std::acos(imageLocations[i].z / sphereRad);
        std::cout << "phi: " << phi << " theta: " << theta << " imageLoc: " << i << std::endl;
        imageLocations[i].x = theta * 180 / M_PI;
        imageLocations[i].y = phi * 180 / M_PI;
        // std::cout << "theta: " << theta << " phi: " << phi << std::endl;
    }

    std::cout << "Getting lab images...\n";
    // std::string imageFileStart = "/home/carson/baxter_ws/run_5/ulfImage", imageFileExt = ".jpg";
    std::string imageFileStart = "/media/carson/WDPassport/iccp/test_3_trim_v2/", imageFileExt = ".jpg";
    std::string imageFile;

    for(int it = 0; it < imageLocations.size(); it++){
        if(it % 1000 == 0){
            std::cout << "it: " << it << std::endl;
        }
        cv::Mat src;
        imageFile = imageFileStart + std::to_string(it) + imageFileExt;
        src = cv::imread(imageFile, 1);
        allImages.push_back(src);
    }

    char commandChar = 'z';
    int i = 0;
    while(true){
    	std::cout << "Direction: ";
    	std::cin >> commandChar;
    	if(commandChar == 'n'){
    		i++;
    		std::cout << "i: " << i << " x: " << realValues[i].x << " y: " << realValues[i].y << " z: " << realValues[i].z << std::endl;
    		std::cout << "theta: " << imageLocations[i].x << " phi: " << imageLocations[i].y << std::endl;
    		cv::imshow("image", allImages[i]);
    	}
    	else if(commandChar == 'b'){
    		i--;
    		std::cout << "i: " << i << " x: " << realValues[i].x << " y: " << realValues[i].y << " z: " << realValues[i].z << std::endl;
    		std::cout << "theta: " << imageLocations[i].x << " phi: " << imageLocations[i].y << std::endl;
    		cv::imshow("image", allImages[i]);
    	}
    	else if(commandChar == 'e'){
    		std::cin >> i;
    		std::cout << "i: " << i << " x: " << realValues[i].x << " y: " << realValues[i].y << " z: " << realValues[i].z << std::endl;
    		std::cout << "theta: " << imageLocations[i].x << " phi: " << imageLocations[i].y << std::endl;
    		cv::imshow("image", allImages[i]);
    	}
    	else{
    		std::cout << "Enter a valid character(n, e, or b)\n";
    	}

    	cv::waitKey(50);
    }

	return 1;
}