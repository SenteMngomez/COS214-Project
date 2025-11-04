/**
 * @file PlantIterator.h
 * @brief Declaration of the PlantIterator class.
 * This class implements the Iterator interface to iterate over a collection of Plant objects.
 * @author Mosa Leiee
 * @date 27 October 2025
 */
#ifndef PLANTITERATOR_H
#define PLANTITERATOR_H

#include "Iterator.h"
#include "Plant.h"
#include <vector>
using namespace std;

/**
 * @class PlantIterator
 * @brief Iterator for Plant objects.
 */
class PlantIterator :public Iterator {
private:
	/// @brief a pointer to a vector of Plant pointers
	vector<Plant*> plants; //vector of Plant pointers
	/// @brief current index in the plants vector
	size_t current;

public:

	/**
	 * @brief Constructor for PlantIterator.
	 * @param plantsVec Vector of Plant pointers to iterate over and sort them according to the tag
	 */
	PlantIterator(const vector<Plant*>& plantsVec);

	/**
	 * @brief Set the iterator to the first Plant object.
	 */
	void first() override;

	/**
	 * @brief Move the iterator to the next Plant object.
	 */
	void next() override;

	/**
	 * @brief Check if the iterator has reached the end of the Plant collection.
	 * @return true if the iterator is done, false otherwise.
	 */
	bool isDone() override;

	/**
	 * @brief Get the current Plant object.
	 * @return Pointer to the current Plant object.
	 */
	Plant* currentItem();
};

#endif
