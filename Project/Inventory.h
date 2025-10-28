/**
 * @file Inventory.h
 * @brief Declaration of Inventory class
 * @author Kundai
 * @date October 26, 2025
 */
#ifndef INVENTORY_H
#define INVENTORY_H

#include "InventoryInterface.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

/**
 * @class Inventory
 * @brief A singleton class that manages the inventory of plants in the nursery.
 * 
 * This class acts as a concrete observer to the Greenhouse and maintains a centralized
 * list of all plants and their stock counts.
 */

class Inventory :public InventoryInterface {

private:

	/// @brief The single, unique instance of the Inventory.
	static Inventory* uniqueInstance;

	/// @brief A map tp store the count of each type of plant.
	std::map<std::string, int> stockCount;

	/// @brief A vector holding pointers to all plant objects in the system.
	std::vector<Plant*> plants;

	/**
	 * @brief Private constructor to enforce Singleton pattern.
	 */
	Inventory();

	/**
	 * @brief Private copy constructor to prevent cloning of the singleton.
	 * @param inventory The inventory to copy from.
	 */
	Inventory(const Inventory& inventory);
	
	/**
	 * @brief Private assignment operator to prevent assignment.
	 * @param inventory The inventory to assign from.
	 * @return A reference to the current instance.
	 */
	Inventory& operator=(Inventory& inventory);
	
public:

	/** 
	 * @brief Provides access to the singleton instance of the Inventory.
	 * @return A pointer to the unique Inventory instance.
	*/
	static Inventory* instance();

	/**
	 * @brief Updates the inventory based on notifications from a subject (e.g. Greenhouse).
	 * 
	 * This method is called by the subjects this observer is attached to. It adds new
	 * plants to the inventory.
	 * @param plant A pointer to the plant that was added or changed. 
	 */
	void updateInventory(Plant* plant);

	/**
	 * @brief Manually adds or updates the stock count for a given plant type.
	 * @param plantName The name of the plant type.
	 * @param stock The number of items to add to the stock.
	 */
	void addStock(string plantName, int stock);
 
	/**
	 * @brief Removes a plant from the inventory by its ID and updates stock count.
	 * @param id The unique identifier of the plant to remove.
	 * @return A pointer to the removed plant, or nullptr if not found.
	 */
	Plant* removePlant(int id);
 
};

#endif
