#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include <string>
using namespace std;

class Plant;

class PlantFactory {

private:
	Plant& product;

public:
	virtual Plant* createPlant(string type) = 0;
};

#endif
