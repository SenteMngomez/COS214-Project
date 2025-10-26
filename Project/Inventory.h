#ifndef INVENTORY_H
#define INVENTORY_H

#include "InventoryInterface.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

class Inventory :public InventoryInterface {

private:

	static Inventory* uniqueInstance;
	std::map<std::string, int> stockCount;
	std::vector<Plant*> plants;

	Inventory();
	Inventory(const Inventory& inventory);
	Inventory& operator=(Inventory& inventory);
	
public:

	static Inventory* instance();

	void updateInventory(Plant* plant);

	void addStock(string plantName, int stock);
 
	Plant* removePlant(int id);
 
};

#endif
