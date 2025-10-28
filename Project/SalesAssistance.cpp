#include "SalesAssistance.h"

Receipt* SalesAssistance::constructReceipt() {
	// TODO - implement SalesAssistance::constructReceipt
	builder->addPrice();
	builder->addPlantDetails();
	builder->addSeller();
	return builder->getReceipt();	
}

void SalesAssistance::setBuilder(ReceiptBuilder* b){
	this->builder = b ;
}