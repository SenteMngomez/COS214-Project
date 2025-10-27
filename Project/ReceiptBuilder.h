#ifndef RECEIPTBUILDER_H
#define RECEIPTBUILDER_H


#include "Receipt.h"


class ReceiptBuilder {

protected:
	Receipt* receipt;

public:
	ReceiptBuilder(){receipt = new Receipt();}

	virtual ~ReceiptBuilder(){};

	virtual void addPrice() = 0;

	virtual void addSeller() = 0;

	virtual void addPlantDetails() = 0;

	//add destructor 
};

#endif
