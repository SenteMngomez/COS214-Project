/**
 * @file GreenhouseInterface.h
 * @brief Implementation of GreenhouseInterface class
 * @author Kundai
 * @date October 24, 2025
 */
#include "GreenhouseInterface.h"

void GreenhouseInterface::attach(InventoryInterface* obs) {
	
	observers.push_back(obs);

}

void GreenhouseInterface::detach(InventoryInterface* obs) {
	
	auto it = std::find(observers.begin(), observers.end(), obs);

	if (it != observers.end()){
		observers.erase(it);
	}

}

void GreenhouseInterface::notify(Plant* plant) {
	
	for (auto observer : observers){
		// Send a clone to inventory so each has independent ownership
		Plant* plantClone = plant->clone();
		observer->updateInventory(plantClone); // Inventory now owns this clone
		//observer->updateInventory(plant);
	}

}
 