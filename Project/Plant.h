/**
 * @file Plant.h
 * @brief Abstract base class for plants in the nursery simulator
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef PLANT_H
#define PLANT_H

#include "PlantState.h"
#include "CareStrategy.h"

#include <string>
using namespace std;
#include <iostream>

/**
 * @class Plant
 * @brief Abstract base class representing a plant in the nursery
 * 
 * Plant encapsulates the core behaviour of nursery plants, including state management
 * (via PlantState), care strategies (via CareStrategy), and lifecycle operations.
 * Supports Prototype pattern through cloning and Decorator pattern through wrapping.
 */

class Plant {

private:
	PlantState* state;
	CareStrategy* careStrategy;
	string colour;
	int tag;
	double price;

public:
	/**
     * @brief Clone the plant (Prototype pattern)
     * @return Pointer to a cloned Plant
     */
	virtual Plant* clone() = 0;

	/**
     * @brief Print plant details
     */
	virtual void print() = 0;

	/**
     * @brief Add a child plant (composite pattern, if applicable)
     * @param plant Reference to the plant to add
     */
	virtual void add(Plant& plant) = 0;

	/**
     * @brief Remove a child plant
     * @param plant Reference to the plant to remove
     */
	virtual void remove(Plant& plant) = 0;

	/**
     * @brief Get a child plant by tag
     * @param tag The tag of the child plant
     */
	virtual void getChild(int tag) = 0;

	/**
     * @brief Construct a Plant with colour and care strategy
     * @param colour The colour of the plant
     * @param careStrategy Pointer to the care strategy
     */
	Plant(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the type of the plant (for stock counting)
     * @return String representing the plant type
     */
    virtual string getType() const = 0;

	/**
     * @brief Get the colour of the plant
     * @return String representing the plant colour
     */
    string getColour() const{ 
		return colour; 
	}

	/**
     * @brief Get the price of the plant
     * @return The price as a double
     */
    double getPrice() const { 
		return price;
	}

    /**
    * @brief Get the tag (unique id) of the plant
    * @return Integer tag
     */
    int getTag() const;

    /**
    * @brief Set the tag (unique id) of the plant
    * @param t Integer tag to set
     */
    void setTag(int t);

    /**
     * @brief Set the state of the plant (for state transitions)
     * @param newState Pointer to the new PlantState
     */
    void setState(PlantState* newState);

	/**
     * @brief destructor
     */
    virtual ~Plant() {}

	/**
     * @brief Receive water from care operations
     */
	void receiveWater();

	/**
     * @brief Receive sunlight from care operations
     */
	void receiveSunlight();

};

#endif
