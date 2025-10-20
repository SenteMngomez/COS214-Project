#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

class PlantFactory {

private:
	Plant& product;

public:
	virtual Plant* createPlant(string type) = 0;
};

#endif
