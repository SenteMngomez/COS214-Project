#ifndef WATERPLANT_H
#define WATERPLANT_H

#include "Command.h"
class WaterPlant :public Command {


public:
	WaterPlant();
	virtual void execute(std::vector<int>* tags,string decorator="");
};

#endif
