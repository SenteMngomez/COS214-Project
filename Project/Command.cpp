#include "Command.h"

Command::Command():greenHouse(nullptr){}

void Command::setGreenhouse(Greenhouse* gh){
	this->greenHouse = gh ;
}