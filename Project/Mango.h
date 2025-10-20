#ifndef MANGO_H
#define MANGO_H

#include "Plant.h"
class Mango :public Plant {


public:
	Plant* clone();

	void print();
};

#endif
