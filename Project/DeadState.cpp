/**
 * @file DeadState.cpp
 * @brief Implementation of the DeadState class methods.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#include "DeadState.h"
#include <iostream>
using namespace std;

/**
 * @brief Handle the state-specific behavior of the plant when it is dead.
 * @param plant Pointer to the Plant object whose state is being handled.
 */

void DeadState::handle(Plant* plant) {
	
	cout<<"The " << plant->getType()<<" is dead and can no longer grow. RIP :"<<endl;
	
}
