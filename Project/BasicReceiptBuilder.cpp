#include "BasicReceiptBuilder.h"

BasicReceiptBuilder::BasicReceiptBuilder(string &seller , vector<Plant*> plants){
	this->sellerName = seller ;
	this->soldPlants = plants;
	// Don't allocate receipt here - base class already did in its constructor
}

void BasicReceiptBuilder::addPrice(){
	double price =0.0 ;
	for(size_t i = 0; i < soldPlants.size(); ++i){
		price += soldPlants[i]->getPrice();
	}
	receipt->setTotalPrice(price);
}

void BasicReceiptBuilder::addPlantDetails(){
	for(size_t i = 0 ; i <soldPlants.size();i++){
		receipt->addPlant(soldPlants[i]->getType(), soldPlants[i]->getPrice());
	}
}

void BasicReceiptBuilder::addSeller(){
	receipt->setSeller(sellerName);
}