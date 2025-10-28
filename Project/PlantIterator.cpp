/**
 * @file PlantIterator.cpp
 * @brief Implementation of the PlantIterator class.
 * @author Mosa Leiee
 * @date 27 October 2025
 */
#include "PlantIterator.h"

PlantIterator::PlantIterator(const vector<Plant*>& plantsVec){
	plants = plantsVec;
	current = 0;
}

void PlantIterator::first() {
	current = 0;
}

void PlantIterator::next() {
	if (current < plants.size()) {
		current++;
	}
}

bool PlantIterator::isDone() {
	return current >= plants.size();
}

Plant* PlantIterator::currentItem() {
	if (!isDone()){
		return plants[current];
	}
	return nullptr;
}
