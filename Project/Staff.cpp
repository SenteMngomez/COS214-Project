#include "Staff.h"

Staff::Staff(std::string name):Person(name){}

void Staff::receiveMessage(Person* person, Section* section){

	std::string plants="";
	std::string decorate="";

	if(person->getMessageType()=="Purchase"){

		plants+="\n\tPurchasing plants: ";

		int numPlants=person->getTags()->size();

		for(int i=0;i<numPlants;i++){

			plants+="Plant-"+to_string((*person->getTags())[i]);

			if(i<numPlants-1){

				plants+=", ";
			}
		}

		if(!person->getDecorator().empty()){

			decorate=" with "+person->getDecorator();

		}
	} else if(person->getMessageType()=="Care"){

		plants+="\n\tPlants to care for: ";

		for(int i=0;i<person->getTags()->size();i++){

			plants+="Plant-"+to_string((*person->getTags())[i])+", ";
		}

	}

		std::cout<<"["<<section->getName()<<"] --"<<person->getMessageType()<<" request-- \""<<person->getMessage()<<"\" from "<<person->getName()<<plants<<decorate;
}

void Staff::handleRequest(Person* person) {

	if(successor){
		successor->handleRequest(person);
	}else{
		std::cout<<"Request Unhandled"<<std::endl;
	}
}

void Staff::setSuccessor(Staff* successor){

	this->successor=successor;
}
