#ifndef SELLPLANT_H
#define SELLPLANT_H

#include "Command.h"
#include <string>
#include <vector>

using namespace std;
class SellPlant :public Command {


public:
	SellPlant();
	void execute(std::vector<int>* tag, string decorator);
};

#endif
