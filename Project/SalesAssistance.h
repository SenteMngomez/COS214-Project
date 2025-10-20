#ifndef SALESASSISTANCE_H
#define SALESASSISTANCE_H

#include "ReceiptBuilder.h"
class Receipt;
class SalesAssistance {

private:
	ReceiptBuilder* builder;

public:
	Receipt* constructReceipt();
	//add destructor 
};

#endif
