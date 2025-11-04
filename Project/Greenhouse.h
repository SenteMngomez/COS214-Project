/**
 * @file Greenhouse.h
 * @brief Declaration of Greenhouse class
 * @author Kundai
 * @date October 24, 2025
 */

#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include "GreenhouseInterface.h"
#include "PlantIterator.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Iterator;

/**
 * @class Greenhouse
 * @brief A concrete subject that manages a collection of plants.
 * 
 * This class represents a physical greenhouse. It can contain plants and perform
 * actions on them, notifying observers of these actions.
 */
class Greenhouse :public GreenhouseInterface {

protected:
	/// @brief The collection of plants currently in this greenhouse.
	std::vector<Plant*> plants;
	/// @brief The name of the greenhouse.
	std::string name;
 
public:

	/**
	 * @brief Constructor for Greenhouse
	 * @param name The name of the greenhouse
	 * 
	 */
	Greenhouse(std::string name) : name(name) {};

	/**
	 * @brief Deletes plants in greenhouse
	 */
	~Greenhouse();
	/** 
	 * @brief Waters a specific plant and notifies observers.
	 * @param plant The plant to water.
	 */
	void waterPlant(std::string tag);

	/**
	 * @brief Gives sunlight to a specific plant and notifies observers.
	 * @param plant The plant to give sunlight to.
	 */
	void giveSunlight(std::string tag);

	/**
	 * @brief Creates an iterator for the plants in the greenhouse.
	 * @return Pointer to an Iterator for the plants.
	 */
	PlantIterator* createIterator();

	/**
	 * @brief Adds a new plant to the greenhouse and notifies observers.
	 * @param plant The plant to add.
	 */
	void addPlant(Plant* plant);

	/**
	 * @brief Didplays information about all plants in the greenhouse to the console.
	 */
	void showPlants();

	/**
	 * @brief Removes a plant from the greenhouse by its tag and notifies observers.
	 * @param tag The unique tag of the plant to remove.
	 * @return A pointer to the removed plant, or nullptr if not found.
	 */
	Plant* removePlant(std::string tag);

	/**
	 * @brief Progresses all plant states
	 */
	void progressPlants();

	/**
	 * @brief Show plants in type order
	 */
	void showOrderedPlants();

	/**
	 * @brief Get the name of the greenhouse
	 * @return The name as a string
	 */
	string getName();
};

#endif
