/**
 * @file Begonia.cpp
 * @brief Implementation of Begonia class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Begonia.h"

Begonia::Begonia(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {
		setTag(getType()+"#"+colour);
	}

Plant* Begonia::clone() {
	return new Begonia(*this);;
}

void Begonia::print() {
	cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
}

Plant* Begonia::getChild(string tag){
	return nullptr;
}