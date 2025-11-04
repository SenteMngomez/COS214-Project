/**
 * @file Cactus.cpp
 * @brief Implementation of Cactus class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Cactus.h"
#include "LightCareStrategy.h"
#include "SeedState.h"

Cactus::Cactus(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {
		setTag(getType()+"#"+colour);
	}

Plant* Cactus::clone() {
    // Create a new CareStrategy of the same type
    CareStrategy* newStrategy = nullptr;
    if (getCareStrategy()) {
        // Assuming all cacti use LightCareStrategy, create a new one
        newStrategy = new LightCareStrategy();
    }
    
    // Create a new Cactus with the same properties but new strategy
    Cactus* cloned = new Cactus(getColour(), newStrategy, getPrice());
    cloned->setTag(getTag());
    
    // Copy the state - create a new state of the same type
    if (getState()) {
        PlantState* newState = new SeedState(); // Default to SeedState for clones
        cloned->setState(newState);
    }
    
    return cloned;
}

void Cactus::print() {
	if(getState()){

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() <<" ("<<getState()->getType()<<")"<<endl;
	}else{

		cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
	}
}

Plant* Cactus::getChild(string tag){
	return nullptr;
}