#ifndef SELLPLANT_H
#define SELLPLANT_H

#include "Command.h"
#include "Inventory.h"
#include "SalesAssistance.h"
#include "BasicReceiptBuilder.h"

#include <string>
#include <vector>

#include <iostream>
using namespace std;
class PlantBuilder;

class SellPlant :public Command {
	private:
		PlantBuilder* builder;
		SalesAssistance* sBuild;
		Receipt* r;


public:
	SellPlant(PlantBuilder* pb);

	void setGreenhouse(Greenhouse* gh);
	void setSalesAssitance(SalesAssistance* sBuild);
	void execute(vector<int>* tag, string decorator="");
};

#endif
