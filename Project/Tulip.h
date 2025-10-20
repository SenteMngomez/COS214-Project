#ifndef TULIP_H
#define TULIP_H

#include "Plant.h"
class Tulip :public Plant {


public:
	Plant* clone();

	void print();
};

#endif
