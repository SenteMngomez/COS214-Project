#include "BasicReceiptBuilder.h"

BasicReceiptBuilder::BasicReceiptBuilder(string &seller , vector<Plant*> plants){
	this->sellerName = seller ;
	this->soldPlants = plants;
	this->receipt = new Receipt();;

}

Receipt* BasicReceiptBuilder::getResult() {
	// TODO - implement BasicReceiptBuilder::getResult
	return this->receipt;
}

void BasicReceiptBuilder::addPrice(){
	double price =0.0 ;
	for(size_t i = 0; i < soldPlants.size(); ++i){
		// price = soldPlants[i].getPrice();
	}
	receipt->setTotalPrice(price);
}

void BasicReceiptBuilder::addPlantDetails(){
	for(size_t i = 0 ; i <soldPlants.size();i++){
		receipt->addPlant(soldPlants[i]);
	}
}

void BasicReceiptBuilder::addSeller(){
	receipt->setSeller(sellerName);
}