#ifndef RECEIPTBUILDER_H
#define RECEIPTBUILDER_H

class ReceiptBuilder {

private:
	Receipt* receipt;

public:
	virtual void addPrice() = 0;

	virtual void addSeller() = 0;

	virtual void addPlantDetails() = 0;

	//add destructor 
};

#endif
