/**
 * @file Mango.cpp
 * @brief Implementation of Mango class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Mango.h"
#include "ModerateCareStrategy.h"
#include "SeedState.h"

Mango::Mango(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {

		setTag(getType()+"#"+colour);
	}

Plant* Mango::clone() {
    // Create a new CareStrategy of the same type
    CareStrategy* newStrategy = nullptr;
    if (getCareStrategy()) {
        // Assuming all mangos use ModerateCareStrategy, create a new one
        newStrategy = new ModerateCareStrategy();
    }
    
    // Create a new Mango with the same properties but new strategy
    Mango* cloned = new Mango(getColour(), newStrategy, getPrice());
    cloned->setTag(getTag());
    
    // Copy the state - create a new state of the same type
    if (getState()) {
        PlantState* newState = new SeedState(); // Default to SeedState for clones
        cloned->setState(newState);
    }
    
    return cloned;
}

void Mango::print() {
	if(getState()){

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() <<" ("<<getState()->getType()<<")"<<endl;
	}else{

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
	}
}

Plant* Mango::getChild(string tag){
	return nullptr;
}