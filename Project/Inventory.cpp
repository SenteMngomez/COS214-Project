#include "Inventory.h"
#include "Plant.h"

Inventory* Inventory::uniqueInstance = nullptr;

Inventory* Inventory::instance() {
	
	if (uniqueInstance == nullptr){
		uniqueInstance = new Inventory();
	}

	return uniqueInstance;

}

Inventory::Inventory() {
	//Empty since we're using singleton
} 

void Inventory::updateInventory(Plant* plant) {
	
	//Checking if plant is not already in inventory
	auto it = std::find(plants.begin(), plants.end(), plant);

	//If plant not found, add to inventory
	if (it == plants.end()){
		plants.push_back(plant);
	}

	//If it is found we don't need to do anything since we already have a pointer

}

void Inventory::addStock(string plantName, int stock) {
	
	stockCount[plantName] += stock;

}

Plant* Inventory::removePlant(int id) {
	
	Plant* removedPlant = nullptr;

	//Find plant by the id
	auto it = std::find_if(plants.begin(), plants.end(), [id](Plant* p){
		return p->getChild(id);
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
