#ifndef SALESASSISTANCE_H
#define SALESASSISTANCE_H

#include "ReceiptBuilder.h"
class Receipt;
class SalesAssistance {

private:
	ReceiptBuilder* builder;

public:
	void setBuilder(ReceiptBuilder* b);
	Receipt* constructReceipt();
	
};

#endif
