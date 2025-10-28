#include "Manager.h"

Manager::Manager(std::string name):Staff(name){}

void Manager::handleRequest(Person* person) {
	
	if(person->getMessageType()=="Help"){

		std::cout<<"(Manager)"<<this->getName()<<" will assist "<<person->getName()<<" with their Help request"<<std::endl;
	}else{

		Staff::handleRequest(person);
	}
}
