/**
 * @file MatureState.cpp
 * @brief Implementation of the MatureState class methods.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#include "MatureState.h"
#include <iostream>
using namespace std;

/**
 * @brief Handle the state-specific behavior of the mature plant.
 * @param plant Pointer to the Plant object whose state is being handled.
 */

void MatureState::handle(Plant* plant) {
	
	cout<<"The plant needs normal care."<<endl;
	plant->receiveWater();
	plant->receiveSunlight();

	cout<<"The plant is aging and may soon die."<<endl;
	plant->setState(new DeadState());

}
