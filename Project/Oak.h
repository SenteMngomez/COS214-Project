#ifndef OAK_H
#define OAK_H
#include "Plant.h"
class Oak :public Plant {


public:
	Plant* clone();

	void print();
};

#endif
