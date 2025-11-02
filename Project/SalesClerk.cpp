#include "SalesClerk.h"

SalesClerk::SalesClerk(std::string name):Staff(name){
	CustomerReceipt = new Receipt();
}

void SalesClerk::handleRequest(Person* person){

	if(person->getMessageType()=="Purchase"){

		std::cout<<"(Sales Clerk)"<<this->getName()<<" will assist "<<person->getName()<<" with their Purchase request"<<std::endl;
		sell(person->getTags(),person->getDecorator());
	}else{

		Staff::handleRequest(person);
	}
}

void SalesClerk::sell(std::vector<int>* tags, string decorator) {
	
	if(sellPlantCommand){
		sellPlantCommand->execute(tags,decorator);
		std::cout<<"I got here-sell function";
		purchaseComplete(sellPlantCommand->getReceipt());
	}else{

		std::cout<<"Unable to make sale\n";
	}
	
}

void SalesClerk::purchaseComplete(std::string msg) {

	std::cout<<"I got here-purchaseComplete function";
	sendMessage(msg,"Purchase Complete");
}

void SalesClerk::setSellPlantCommand(SellPlant* sellPlantCommand){

	this->sellPlantCommand=sellPlantCommand;
}