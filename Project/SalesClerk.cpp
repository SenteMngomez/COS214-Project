#include "SalesClerk.h"

SalesClerk::SalesClerk(std::string name):Staff(name),sellPlantCommand(nullptr){
	
}

void SalesClerk::handleRequest(Person* person){

	if(person->getMessageType()=="Purchase"){

		if(person->getTags()->empty()){
			
			return;
		}

		std::cout<<"(Sales Clerk)"<<this->getName()<<" will assist "<<person->getName()<<" with their Purchase request"<<std::endl;
		sell(person->getTags(),person->getDecorator(),person->getName());
	}else{

		Staff::handleRequest(person);
	}
}

void SalesClerk::sell(std::vector<string>* tags, string decorator, string name) {
	
	if(sellPlantCommand){
		sellPlantCommand->execute(tags,decorator);
		purchaseComplete(sellPlantCommand->getReceipt(), name);
	}else{

		std::cout<<"Unable to make sale\n";
	}
	
}

void SalesClerk::purchaseComplete(std::string msg,string name) {

	sendMessage(msg,"Purchase Complete",nullptr,name);
}

void SalesClerk::setSellPlantCommand(SellPlant* sellPlantCommand){

	this->sellPlantCommand=sellPlantCommand;
}