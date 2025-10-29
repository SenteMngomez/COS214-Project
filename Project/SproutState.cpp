/**
 * @file SproutState.cpp
 * @brief Implementation of the SproutState class methods.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#include "SproutState.h"
#include <iostream>
using namespace std;

/**
 * @brief Handle the state-specific behavior of the sprout.
 * @param plant Pointer to the Plant object whose state is being handled.
 */

void SproutState::handle(Plant* plant) {
	
	cout<<"The " <<plant->getType() <<" sprout is growing and needs care."<<endl;
	plant->receiveWater();
	plant->receiveSunlight();

	cout<<"The sprout has finally matured into a full "<<plant->getType()<<". #grown"<<endl;
	plant->setState(new MatureState());
}
