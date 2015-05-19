#ifndef __GAUSSIAN_PROCESS_H
#define __GAUSSIAN_PROCESS_H

#include <vector>

#include "predictor_node_lib.h"

/*
Header file with basic tools for interpolation and regression
using Gaussian processes
*/

//Univariate Guassian density
void univarGauss(std::vector<ValueBlock *> &);

void multiVarGauss(std::vector<ValueBlock *> &);

#endif