#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <time.h>

int main(int argc, char **argv)
{

	// Seed time
	srand(time(NULL));

	float newVal;
	int nSamp = 10;
	std::vector<float> samples;
	float mean = 0, variance = 0, stdDev = 0, sum, sumSquares;

	// Populate vector with values between 4 and 6;
	for(int i = 0; i < nSamp; i++)
	{
		samples.push_back(rand() % 10 + 1);
	}

	while(true)
	{
		// Re-Initialize vars
		sum = 0;
		sumSquares = 0;

		// Calculate mean and stdDev and variance
		for(int i = 0; i < samples.size(); i++)
		{
			sum += samples[i];
			sumSquares += samples[i] * samples[i];
		}

		mean = sum/nSamp;
		variance = (sumSquares - (sum * sum) / nSamp) / (nSamp - 1);
		stdDev = sqrt(variance);

		// Print results
		std::cout << "mean: " << mean << " stdDev: " << stdDev << " variance: " << variance << std::endl;

		// Print data
		std::cout << "\nData in vector" << std::endl;
		for(int i = 0; i < nSamp; i++)
		{
			std::cout << samples[i] << std::endl;
		}

		// Add new value
		std::cout << "Enter new value: ";
		std::cin >> newVal;

		// Erase first value, add new val
		samples.erase(samples.begin());
		samples.push_back(newVal);

		//Print data again
		std::cout << "New data: " << std::endl;
		for(int i = 0; i < samples.size(); i++)
		{
			std::cout << samples[i] << std::endl;
		}
	}	

	return 1;
}