#ifndef CACTUS_H
#define CACTUS_H

#include "Plant.h"

class Cactus :public Plant {


public:
	Plant* clone();

	void print();
};

#endif
