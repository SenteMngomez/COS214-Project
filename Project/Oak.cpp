/**
 * @file Oak.cpp
 * @brief Implementation of Oak class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Oak.h"
#include "ModerateCareStrategy.h"
#include "SeedState.h"

Oak::Oak(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {
		setTag(getType()+"#"+colour);
	}

Plant* Oak::clone() {
    // Create a new CareStrategy of the same type
    CareStrategy* newStrategy = nullptr;
    if (getCareStrategy()) {
        // Assuming all oaks use ModerateCareStrategy, create a new one
        newStrategy = new ModerateCareStrategy();
    }
    
    // Create a new Oak with the same properties but new strategy
    Oak* cloned = new Oak(getColour(), newStrategy, getPrice());
    cloned->setTag(getTag());
    
    // Copy the state - create a new state of the same type
    if (getState()) {
        PlantState* newState = new SeedState(); // Default to SeedState for clones
        cloned->setState(newState);
    }
    
    return cloned;
}

void Oak::print() {
	if(getState()){

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() <<" ("<<getState()->getType()<<")"<<endl;
	}else{

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
	}

}

Plant* Oak::getChild(string tag){
	return nullptr;
}