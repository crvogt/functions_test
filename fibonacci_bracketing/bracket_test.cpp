#include <vector>
#include <iostream>

int main(int argc, char **argv){
	/**************fibonacci exp bracketing*************/
	// Set number of exposures in time T
	float T = 1000.0; //ms
	float exposure = 3.0;
	float exposure_sum = 0.0;
	float temp_exp1 = 0.0;
	float temp_exp2 = 0.0;
	std::vector<float> exposure_vec;
	int counter = 0;

	while(exposure_sum <= T){
		if(counter == 0){
			exposure_vec.push_back(exposure);
			exposure_sum += exposure;
			temp_exp1 = exposure;
			temp_exp2 = exposure;
			counter++;
		}
		else{
			exposure = temp_exp1 + temp_exp2;
			if((exposure_sum + exposure) < T){
				exposure_sum += exposure;
				exposure_vec.push_back(exposure);
				temp_exp1 = temp_exp2;
				temp_exp2 = exposure;
				counter++;
			}
			else{
				break;
			}
		}
	}

	std::cout << "\nNumber of exposures: " << counter + 1 << std::endl;
	std::cout << "\nTotal exposure time: " << exposure_sum << std::endl;

	std::cout << "Exposures:\n";
	for(int i = 0; i < exposure_vec.size(); i++){
		std::cout << exposure_vec[i] << std::endl;
	}
	std::cout << std::endl;

	return 1;
}