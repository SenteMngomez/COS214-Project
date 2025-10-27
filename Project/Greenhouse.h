#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include "GreenhouseInterface.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Iterator;

class Greenhouse :public GreenhouseInterface {

protected:

	std::vector<Plant*> plants;
	string name;
 
public:
	void waterPlant(Plant* plant);

	void giveSunlight(Plant* plant);

	virtual Iterator* createIterator() = 0;

	void addPlant(Plant* plant);

	void showPlants();

	Plant* removePlant(int tag);

	string getName();
};

#endif
