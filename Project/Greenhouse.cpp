/**
 * @file Greenhouse.cpp
 * @brief Implementation of Greenhouse class
 * @author Kundai
 * @date October 24, 2025
 */
#include "Greenhouse.h"

void Greenhouse::waterPlant(int tag) {
	
	Plant* wateredPlant = nullptr;

	auto it = std::find_if(plants.begin(), plants.end(), [tag](Plant* p) { //Finding plant with tag in order to water
		return p->getTag() == tag;
	});

	if (it != plants.end()){

		wateredPlant =*it;
		wateredPlant->receiveWater();
		notify(wateredPlant); 
		
	}

}

void Greenhouse::giveSunlight(int tag) {
	
	Plant* sunBathedPlant = nullptr;

	auto it = std::find_if(plants.begin(), plants.end(), [tag](Plant* p) { //Finding plant with tag in order to give sunlight
		return p->getTag() == tag;
	});

	if (it != plants.end()){

		sunBathedPlant = *it;
		sunBathedPlant->receiveSunlight();
		notify(sunBathedPlant); 
		
	}

}

Iterator *Greenhouse::createIterator()
{
    return new PlantIterator(plants);
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
		return p->getTag() == tag;
	});

	if (it != plants.end()){

		removedPlant =*it; 
		plants.erase(it);
		notify(removedPlant); //Notify observers about the removed plant
		
	}

	return removedPlant; 

}

string Greenhouse::getName()
{
    return name;
}
