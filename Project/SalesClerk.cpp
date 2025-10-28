#include "SalesClerk.h"

void SalesClerk::handleRequest(Person* person){

	if(person->getMessageType()=="Purchase"){

		std::cout<<"Sales Clerk-"<<this->getName()<<" will assist "<<person->getName()<<" with their Purchase request"<<std::endl;
		sell(person->getTags(),person->getDecorator());
	}else{

		Staff::handleRequest(person);
	}
}

void SalesClerk::sell(std::vector<int>* tags, string decorator) {
	
	if(sellPlantCommand){
		sellPlantCommand->execute(tags,decorator);

	}else{

		std::cout<<"Unable to make sale";
	}
	
}

void SalesClerk::purchaseComplete(std::string msg) {

	sendMessage(msg,"Purchase Complete");
}

void SalesClerk::setSellPlantCommand(SellPlant* sellPlantCommand){

	this->sellPlantCommand=sellPlantCommand;
}