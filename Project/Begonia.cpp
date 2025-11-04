/**
 * @file Begonia.cpp
 * @brief Implementation of Begonia class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Begonia.h"
#include "LightCareStrategy.h"
#include "SeedState.h"

Begonia::Begonia(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {
		setTag(getType()+"#"+colour);
	}

Plant* Begonia::clone() {
    // Create a new CareStrategy of the same type
    CareStrategy* newStrategy = nullptr;
    if (getCareStrategy()) {
        // Assuming all begonias use LightCareStrategy, create a new one
        newStrategy = new LightCareStrategy();
    }
    
    // Create a new Begonia with the same properties but new strategy
    Begonia* cloned = new Begonia(getColour(), newStrategy, getPrice());
    cloned->setTag(getTag());
    
    // Copy the state - create a new state of the same type
    if (getState()) {
        PlantState* newState = new SeedState(); // Default to SeedState for clones
        cloned->setState(newState);
    }
    
    return cloned;
}

void Begonia::print() {
	if(getState()){

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() <<" ("<<getState()->getType()<<")"<<endl;
	}else{

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
	}
}

Plant* Begonia::getChild(string tag){
	return nullptr;
}