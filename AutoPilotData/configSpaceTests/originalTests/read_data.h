#ifndef __READ_DATA_H
#define __READ_DATA_H

#include <string>
#include <vector>
#include "predictor_node_lib.h"

class ReadCSVValues{
public:
	int read(std::vector<ValueBlock>, const string filename);
	int write(std::vector<ValueBlock>, const string filename);
};

#endif