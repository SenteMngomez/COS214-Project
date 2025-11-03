/**
 * @file Oak.cpp
 * @brief Implementation of Oak class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Oak.h"

Oak::Oak(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {
		setTag(getType()+"#"+colour);
	}

Plant* Oak::clone() {
	return new Oak(*this);
}

void Oak::print() {
	 cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
}

Plant* Oak::getChild(string tag){
	return nullptr;
}