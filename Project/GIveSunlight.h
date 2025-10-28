#ifndef GIVESUNLIGHT_H
#define GIVESUNLIGHT_H

#include "Command.h"
class GiveSunlight :public Command {


public:
	GiveSunlight();
	virtual void execute(std::vector<int>* tags,string decorator="");
};

#endif
