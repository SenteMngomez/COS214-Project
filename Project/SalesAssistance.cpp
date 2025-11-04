#include "SalesAssistance.h"

Receipt* SalesAssistance::constructReceipt() {
	// TODO - implement SalesAssistance::constructReceipt
	builder->addPrice();
	builder->addPlantDetails();
	builder->addSeller();
	return builder->getReceipt();
}

SalesAssistance::~SalesAssistance(){

	if(builder){
		delete builder;
		builder=nullptr;
	}
}

void SalesAssistance::setBuilder(ReceiptBuilder* b){
	if(builder && builder!=b){ delete builder; }
	this->builder = b ;
}