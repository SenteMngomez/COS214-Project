#ifndef SELLPLANT_H
#define SELLPLANT_H

#include "Command.h"
#include <string>

using namespace std;
class SellPlant :public Command {


public:
	void execute(int* tag, string decorator);
};

#endif
