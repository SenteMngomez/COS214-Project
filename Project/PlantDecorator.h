#ifndef PLANTDECORATOR_H
#define PLANTDECORATOR_H

#include "Plant.h"

class PlantDecorator :public Plant {

public:
	Plant* component;

	void print();
};

#endif
