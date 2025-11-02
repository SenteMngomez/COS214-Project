/**
 * @file GreenhouseInterface.h
 * @brief Interface for Greenhouse class (Subject in Observer pattern)
 * @author Kundai
 * @date October 24, 2025
 */
#ifndef GREENHOUSEINTERFACE_H
#define GREENHOUSEINTERFACE_H

#include "InventoryInterface.h"
#include <vector>
#include <algorithm>

/**
 * @class GreenhouseInterface
 * @brief An interface for the "Subject" in the Observer design pattern.
 * 
 * This class allows observers (like Inventory) to attach and detach, and it provides 
 * a mechanism to notify them of changes.
 */
class GreenhouseInterface {


public:
	/**
	 * @brief Attaches an observer to this subject.
	 * @param obs A pointer to the observer to attach.
	 */
	void attach(InventoryInterface* obs);

	/**
	 * @brief Detaches an observer from this subject.
	 * @param obs A pointer to the observer to detach.
	 */
	void detach(InventoryInterface* obs);

protected:
	/// @brief A list of pointers to all attached observers.
	std::vector<InventoryInterface*> observers;

	/**
	 * @brief Notifies all attached observers of a change.
	 * @param plant A pointer to the plant that has been affected.
	 */
	void notify(Plant* plant);
	
};

#endif 
