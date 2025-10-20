#ifndef FLOWERFACTORY_H
#define FLOWERFACTORY_H

#include "PlantFactory.h"

#include <string>
class Plant;
using namespace std;
class FlowerFactory :public PlantFactory {


public:
	Plant* createPlant(string type);
};

#endif
