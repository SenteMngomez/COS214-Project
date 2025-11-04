/**
 * @file Inventory.cpp
 * @brief Implementation of Inventory class
 * @author Kundai
 * @date October 26, 2025
 */
#include "Inventory.h"
#include "Plant.h"

Inventory* Inventory::uniqueInstance = nullptr;

Inventory* Inventory::instance() {
	
	if (uniqueInstance == nullptr){
		uniqueInstance = new Inventory();
	}

	return uniqueInstance;

}

void Inventory::cleanup() {
	if (uniqueInstance != nullptr) {
		delete uniqueInstance;
		uniqueInstance = nullptr;
	}
}

Inventory::Inventory() {
	//Empty since we're using singleton
}

Inventory::~Inventory() {
	// Clean up all plant clones owned by inventory
	for(Plant* plant : plants) {
		delete plant;
	}
	plants.clear();
}

Inventory::Inventory(const Inventory &inventory)
{
	//Empty since we're using singleton
}

void Inventory::updateInventory(Plant* plant) {
	
	// Since we now receive clones, we always add them to inventory
	// No need to check for duplicates since each is a unique clone
	plants.push_back(plant);
	stockCount[plant->getType()]++;

	// auto it = std::find(plants.begin(), plants.end(), plant);

	// //If plant not found, add to inventory
	// if (it == plants.end()){
	// 	plants.push_back(plant);
	// 	stockCount[plant->getType()]++;
	// }

}

void Inventory::clearInventory(){
	// Delete all plant objects before clearing the vector
	for (Plant* plant : plants) {
		delete plant;
	}
	plants.clear();
	stockCount.clear();
}

void Inventory::addStock(string plantName, int stock) {
	
	stockCount[plantName] += stock;

}

Plant* Inventory::removePlant(std::string id) {
	
	Plant* removedPlant = nullptr;

	//Find plant by the id
	auto it = std::find_if(plants.begin(), plants.end(), [id](Plant* p){
		return p->getTag() == id;
	});

	if (it != plants.end()){
		removedPlant = *it;
		plants.erase(it);
		stockCount[removedPlant->getType()]--;//updating stockCount 
	}

	return removedPlant;

}

Inventory& Inventory::operator=(Inventory& inventory) {
	
	return *this; //returning the current instance

}
