#ifndef GIVESUNLIGHT_H
#define GIVESUNLIGHT_H

#include "Command.h"
class GIveSunlight :public Command {


public:
	virtual void execute(int* tag,string decorator="");
};

#endif
