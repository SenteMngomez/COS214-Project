#ifndef BEGONIA_H
#define BEGONIA_H

#include "Plant.h"

class Begonia :public Plant {


public:
	Plant* clone();

	void print();
};

#endif
