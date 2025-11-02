/**
 * @file SeedState.cpp
 * @brief Implementation of the SeedState class methods.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#include "SeedState.h"
#include <iostream>
using namespace std;

/**
 * @brief Handle the seed state behavior of the plant.
 * @param plant Pointer to the Plant object whose state is being handled.
 */

void SeedState::handle(Plant* plant) {
	
	cout<<"Germinating from seed to sprout. Critical phase!"<<endl;
	plant->receiveWater();
	plant->receiveSunlight();

	cout<<"Seed has successfully germinated into a " << plant->getType()<< " sprout!"<<endl;
	plant->setState(new SproutState());
}
