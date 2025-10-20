#ifndef INVENTORY_H
#define INVENTORY_H

#include "InventoryInterface.h"

class Inventory :public InventoryInterface {

public:
	Inventory* uniqueInstance;

	Inventory* instance();

	Inventory();

	void updateInventory(Plant* plant);

	Inventory(Inventory& inventory);

	void addStock(string plantName, int stock);

	Plant* removePlant(int id);

	Inventory& operator=(Inventory& inventory);
};

#endif
