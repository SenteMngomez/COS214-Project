/**
 * @file Plant.cpp
 * @brief Implementation of the Plant base class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Plant.h"
#include "SeedState.h"

Plant::Plant(string colour, CareStrategy* careStrategy, double price)
    : colour(colour), careStrategy(careStrategy), state(NULL), tag(""), price(price){
    // come back for review on initializing state 
}

void Plant::receiveWater() {
	if(careStrategy){
        careStrategy->water(this);
    }
    //cout << getType() << " plant received water." << endl;
}

void Plant::receiveSunlight() {
	if(careStrategy) {
        careStrategy->sunlight(this);
    }
    //cout << getType() << " plant received sunlight." << endl;
}

string Plant::getTag() const{
	return tag;
}

void Plant::setTag(string t){
	tag = t;
}

CareStrategy* Plant::getCareStrategy(){
	return careStrategy;
}

void Plant::setState(PlantState* newState) {
    if(state){
        delete state;  
    }
    state = newState;
}

// PlantState* Plant::getState() const {
//     return state;
// }

void Plant::setCareStrategy(CareStrategy* careStrategy){
	this->careStrategy=careStrategy;
}





