#ifndef SELLPLANT_H
#define SELLPLANT_H

#include "Command.h"
#include "Inventory.h"

#include <string>
#include <vector>

#include <iostream>
using namespace std;
class PlantBuilder;

class SellPlant :public Command {
	private:
		PlantBuilder* builder;


public:
	SellPlant(PlantBuilder* pb);


	void execute(vector<int>* tag, string decorator="");
};

#endif
