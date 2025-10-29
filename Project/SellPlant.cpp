#include "SellPlant.h"
#include "PlantBuilder.h"

SellPlant::SellPlant(PlantBuilder* pb):Command(){}

void SellPlant::execute(vector<int>* tag, string decorator) {
	// TODO - implement SellPlant::execute
	if(!tag){
		return ;
	}
	vector<Plant*> soldPlants;
	for(int i :*tag){
		if(inventory){
			 Plant* p = greenHouse->removePlant(i);
        	if (p) soldPlants.push_back(p);
		}
	}

	if (soldPlants.empty()) return;

    Plant* saleItem = builder->buildCompositePlant(soldPlants, decorator);

    std::cout << "Selling " 
              << (soldPlants.size() > 1 ? "group of plants" : "single plant")
              << " from greenhouse " << greenHouse->getName() << std::endl;


	
}
