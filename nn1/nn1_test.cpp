#include <iostream>
#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

class neuron{
private:
	std::vector<float> weights;
	float bias;
	float activation;
	void relu();
public:
	neuron();
	void input();
	float output();
};

class layer{

};

int main(int argc, char **argv){
	layer output;
	layer hidden;
	layer hidden;
	layer input;
	return 1;
}