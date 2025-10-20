#ifndef SUCCULENTFACTORY_H
#define SUCCULENTFACTORY_H


#include "PlantFactory.h"
#include <string>
using namespace std;
class Plant;
class SucculentFactory :public PlantFactory {


public:
	Plant* createPlant(string type);
};

#endif
