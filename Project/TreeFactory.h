#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "PlantFactory.h"
#include <string>
using namespace std;
class Plant;
class TreeFactory :public PlantFactory {


public:
	Plant* createPlant(string type);
};

#endif
