/**
 * @file Plant.cpp
 * @brief Implementation of the Plant base class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Plant.h"

Plant::Plant(string colour, CareStrategy* careStrategy, double price)
    : colour(colour), careStrategy(careStrategy), state(NULL), tag(0), price(price){
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

int Plant::getTag() const{
	return tag;
}

void Plant::setTag(int t){
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

void Plant::setCareStrategy(CareStrategy* careStrategy){
	this->careStrategy=careStrategy;
}



