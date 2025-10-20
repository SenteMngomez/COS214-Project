#ifndef PLANTGROUP_H
#define PLANTGROUP_H

#include 	"Plant.h"

class PlantGroup :public Plant {

public:
	Plant* children;

	void print();

	void add(Plant* plant);

	void remove(Plant* plant);

	void getChild(int tag);
};

#endif
