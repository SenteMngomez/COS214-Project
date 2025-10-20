#ifndef WATERPLANT_H
#define WATERPLANT_H

#include "Command.h"
class WaterPlant :public Command {


public:
	virtual void execute(int* tag,string decorator="");
};

#endif
