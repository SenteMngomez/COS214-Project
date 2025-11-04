#ifndef RECEIPTBUILDER_H
#define RECEIPTBUILDER_H


#include "Receipt.h"


class ReceiptBuilder {

protected:
	Receipt* receipt;

public:
	ReceiptBuilder(){receipt = new Receipt();}

	virtual ~ReceiptBuilder(){
		if(receipt){
			delete receipt;
			receipt = nullptr;
		}
		
	}

	virtual void addPrice() = 0;

	virtual void addSeller() = 0;

	virtual void addPlantDetails() = 0;

	Receipt* getReceipt(){
		Receipt* temp = receipt;
		receipt = nullptr; // Transfer ownership to caller
		return temp;
	}
	//add destructor 
};

#endif
