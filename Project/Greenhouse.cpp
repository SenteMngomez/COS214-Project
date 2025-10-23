#include "Greenhouse.h"

void Greenhouse::waterPlant(Plant* plant) {
	
	plant->receiveWater();
	notify(plant);

}

void Greenhouse::giveSunlight(Plant* plant) {
	
	plant->receiveSunlight();
	notify(plant);

}

void Greenhouse::addPlant(Plant* plant) {
	
	plants.push_back(plant);
	notify(plant); // Notify observers about the new plant

}

void Greenhouse::showPlants() {
	
	if (plants.empty()){
		std::cout << "No plants in the greenhouse." << std::endl;
		return;
	}

	std::cout << "Plants in the greenhouse:" << std::endl;
	std::cout << "------------------------" << std::endl;

	for (Plant* plant: plants){
		plant->print();
	}
}

Plant* Greenhouse::removePlant(int tag) {
	
	Plant* removedPlant = nullptr;

	auto it = std::find_if(plants.begin(), plants.end(), [tag](Plant* p) {
		return p->getChild(tag);
	});

	if (it != plants.end()){
		removedPlant =*it;
		plants.erase(it);
		notify(removedPlant); //Notify observers about the removed plant
	}

	return removedPlant;

}
