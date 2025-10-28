#ifndef BASICRECEIPTBUILDER_H
#define BASICRECEIPTBUILDER_H

#include "ReceiptBuilder.h"

#include "Plant.h"
#include <vector>

class BasicReceiptBuilder :public ReceiptBuilder {
private:
	string sellerName;
	vector<Plant*> soldPlants;


public:
	BasicReceiptBuilder( string & seller, vector<Plant*> plants);

	Receipt* getResult();

	virtual void addPrice();

	virtual void addSeller();

	virtual void addPlantDetails();
};

#endif
