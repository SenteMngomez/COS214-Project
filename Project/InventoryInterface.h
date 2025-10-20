#ifndef INVENTORYINTERFACE_H
#define INVENTORYINTERFACE_H


#include "Plant.h"
class InventoryInterface {


public:
	virtual void updateInventory(Plant* plant) = 0;
};

#endif
