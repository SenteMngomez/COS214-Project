#ifndef BASICRECEIPTBUILDER_H
#define BASICRECEIPTBUILDER_H

#include "ReceiptBuilder.h"
#include "Receipt.h"

class BasicReceiptBuilder :public ReceiptBuilder {


public:
	Receipt* getResult();

	virtual void addPrice();

	virtual void addSeller();

	virtual void addPlantDetails();
};

#endif
