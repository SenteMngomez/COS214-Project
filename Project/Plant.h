#ifndef PLANT_H
#define PLANT_H

#include "PlantState.h"
#include "CareStrategy.h"

#include <string>
using namespace std;

class Plant {

private:
	PlantState* state;
	CareStrategy* careStrategy;
	string colour;
	int tag;

public:
	virtual Plant* clone() = 0;

	virtual void print() = 0;

	virtual void add(Plant plant) = 0;

	virtual void remove(Plant plant) = 0;

	virtual void getChild(int tag) = 0;

	Plant(string colour, CareStrategy* careStrategy);

	void receiveWater();

	void receiveSunlight();

	//add destructor 
};

#endif
