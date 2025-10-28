#ifndef INVENTORYINTERFACE_H
#define INVENTORYINTERFACE_H


#include "Plant.h"

/**
 * class InventoryInterface
 * @brief An interface for the "Observer" in the Observer design pattern.
 * 
 * Classes that implement this interface can register with a subject (like Greenhouse)
 * to receive notifications about changes.
 */
class InventoryInterface {

public:
	/**
	 * @brief The update method called by the subject to notify the observer of a change.
	 * @param plant A pointer to the plant that has been affected.
	 */
	virtual void updateInventory(Plant* plant) = 0;
};

#endif
