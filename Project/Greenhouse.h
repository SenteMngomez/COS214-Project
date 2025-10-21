#ifndef GREENHOUSE_H
#define GREENHOUSE_H


#include "GreenhouseInterface.h"
#include <vector>
#include <string>

class Iterator;

class Greenhouse :public GreenhouseInterface {

private:
	std::vector<Plant*> plants;
	string name;

public:
	void waterPlant(Plant* plant);

	void giveSunlight(Plant* plant);

	virtual Iterator* createIterator() = 0;

	void addPlant(Plant* plant);

	void showPlants();

	Plant* removePlant(int tag);
};

#endif
