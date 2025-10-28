/**
 * @file PlantGroup.h
 * @brief Composite PlantGroup class for grouping plants
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef PLANTGROUP_H
#define PLANTGROUP_H

#include "Plant.h"
#include <vector>

using namespace std;

/**
 * @class PlantGroup
 * @brief Composite class for grouping multiple plants
 * 
 * PlantGroup allows treating a collection of plants as a single unit.
 * Implements composite pattern for hierarchical plant structures.
 */
class PlantGroup :public Plant {

private:
    vector<Plant*> children;
	vector<string> types;

public:
	/**
     * @brief Construct a PlantGroup with colour, care strategy, and price
     * @param colour The colour of the group
     * @param careStrategy Pointer to care strategy
     * @param price The price of the group
     */
    PlantGroup(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the types of the plants in the group
     * @return Comma-separated string of types (e.g., "Rose, Cactus"), or "PlantGroup" if empty
     */
    string getType() const override;

	/**
     * @brief Clone the plant group and its children
     * @return Pointer to a new PlantGroup with cloned children
     */
    Plant* clone() override;

	//Plant* children;

	/**
     * @brief Print the group and its children
     */
	void print();

	/**
     * @brief Add a child plant to the group
     * @param plant Reference to the plant to add
     */
    void add(Plant& plant) override;

	/**
     * @brief Remove a child plant from the group
     * @param plant Reference to the plant to remove
     */
    void remove(Plant& plant) override;

	/**
     * @brief Get a child plant by tag
     * @param tag The tag of the child plant
     */
    void getChild(int tag) override;

	/**
     * @brief Destructor to clean up children
     */
    ~PlantGroup() override;
};

#endif
