#ifndef RECEIPTBUILDER_H
#define RECEIPTBUILDER_H


#include "Receipt.h"


class ReceiptBuilder {

protected:
	/// @brief The receipt being built
	Receipt* receipt;

public:
	/**
	 * @brief Constructor for ReceiptBuilder
	 */
	ReceiptBuilder(){receipt = new Receipt();}

	/**
	 * @brief Destructor for ReceiptBuilder
	 */
	virtual ~ReceiptBuilder(){
		if(receipt){
			delete receipt;
			receipt = nullptr;
		}
		
	}

	/**
	 * @brief Build the receipt's total price
	 */
	virtual void addPrice() = 0;

	/**
	 * @brief Build the receipt's seller information
	 */
	virtual void addSeller() = 0;

	/**
	 * @brief Build the receipt's plant details
	 */
	virtual void addPlantDetails() = 0;

	/**
	 * @brief Get the built receipt
	 * @return Pointer to the built Receipt
	 */
	Receipt* getReceipt(){
		Receipt* temp = receipt;
		receipt = nullptr; // Transfer ownership to caller
		return temp;
	}
	//add destructor 
};

#endif
