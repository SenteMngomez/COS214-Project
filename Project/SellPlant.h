#ifndef SELLPLANT_H
#define SELLPLANT_H

#include "Command.h"
#include "Inventory.h"
#include <string>
#include <vector>

#include <iostream>
using namespace std;
class SellPlant :public Command {


public:
	void execute(vector<int>* tag, string decorator="");
};

#endif
