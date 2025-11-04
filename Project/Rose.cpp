/**
 * @file Rose.cpp
 * @brief Implementation of Rose class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Rose.h"
#include "HeavyCareStrategy.h"
#include "SeedState.h"

Rose::Rose(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {

		setTag(getType()+"#"+colour);
	}

Plant* Rose::clone() {
    // Create a new CareStrategy of the same type
    CareStrategy* newStrategy = nullptr;
    if (getCareStrategy()) {
        // Assuming all roses use HeavyCareStrategy, create a new one
        newStrategy = new HeavyCareStrategy();
    }
    
    // Create a new Rose with the same properties but new strategy
    Rose* cloned = new Rose(getColour(), newStrategy, getPrice());
    cloned->setTag(getTag());
    
    // Copy the state - create a new state of the same type
    if (getState()) {
        PlantState* newState = new SeedState(); // Default to SeedState for clones
        cloned->setState(newState);
    }
    
    return cloned;
}

void Rose::print() {
	if(getState()){

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() <<" ("<<getState()->getType()<<")"<<endl;
	}else{

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
	}
}

Plant* Rose::getChild(string tag){
	return nullptr;
}
