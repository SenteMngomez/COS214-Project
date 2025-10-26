#include "Customer.h"

	Customer::Customer(std::string name):Person(name){}

	void Customer::receiveMessage(Person* person, Section* section){

		if(person->getMessageType()=="Purchase"||person->getMessageType()=="Care"){
			return;
		}

		std::cout<<"["<<section->getName()<<"] --"<<person->getMessageType()<<"-- \""<<person->getMessage()<<"\" from "<<person->getName();

	}
