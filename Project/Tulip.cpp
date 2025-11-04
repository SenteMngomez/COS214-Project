/**
 * @file Tulip.cpp
 * @brief Implementation of Tulip class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Tulip.h"
#include "HeavyCareStrategy.h"
#include "SeedState.h"

Tulip::Tulip(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {

		setTag(getType()+"#"+colour);
	}

Plant* Tulip::clone() {
    // Create a new CareStrategy of the same type
    CareStrategy* newStrategy = nullptr;
    if (getCareStrategy()) {
        // Assuming all tulips use HeavyCareStrategy, create a new one
        newStrategy = new HeavyCareStrategy();
    }
    
    // Create a new Tulip with the same properties but new strategy
    Tulip* cloned = new Tulip(getColour(), newStrategy, getPrice());
    cloned->setTag(getTag());
    
    // Copy the state - create a new state of the same type
    if (getState()) {
        PlantState* newState = new SeedState(); // Default to SeedState for clones
        cloned->setState(newState);
    }
    
    return cloned;
}

void Tulip::print() {
	if(getState()){

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() <<" ("<<getState()->getType()<<")"<<endl;
	}else{

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
	}
}

Plant* Tulip::getChild(string tag){
	return nullptr;
}
