#include "SellPlant.h"
#include "PlantBuilder.h"

SellPlant::SellPlant(PlantBuilder* pb){
	this->builder = pb;
	sBuild = new SalesAssistance();
	r = nullptr;
}

void SellPlant::setGreenhouse(Greenhouse* gh){
	this->greenHouse = gh ;
}

void SellPlant::setSalesAssitance(SalesAssistance* sa){
    if(sBuild != sa){
        delete sBuild;
        sBuild = sa;
    }
}
void SellPlant::execute(vector<int>* tag, string decorator){
	vector<Plant*> soldPlants;
	for(int i :*tag){
		if(inventory){
			 Plant* p = greenHouse->removePlant(i);
        	if (p) soldPlants.push_back(p);
		}
	}

	if (soldPlants.empty()) return;

    Plant* saleItem = builder->buildCompositePlant(soldPlants, decorator);
	string sellerName = "Green Home"; // Or get from somewhere
    BasicReceiptBuilder* receiptBuilder = new BasicReceiptBuilder(sellerName, soldPlants);

	sBuild->setBuilder(receiptBuilder);
	r = sBuild->constructReceipt();
	if(r){
		r->print();
	}
    std::cout << "Selling " 
              << (soldPlants.size() > 1 ? "group of plants" : "single plant")
              << " from greenhouse " << greenHouse->getName() << std::endl;

	delete receiptBuilder;
	
}
