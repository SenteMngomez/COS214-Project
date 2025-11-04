#ifndef SALESASSISTANCE_H
#define SALESASSISTANCE_H

#include "ReceiptBuilder.h"
class Receipt;
class SalesAssistance {

private:
	/// @brief The receipt builder
	ReceiptBuilder* builder;

public:
	/**
	 * @brief Constructor for SalesAssistance
	 */
	~SalesAssistance();

	/**
	 * @brief Set the receipt builder
	 * @param b Pointer to the ReceiptBuilder
	 */
	void setBuilder(ReceiptBuilder* b);

	/**
	 * @brief Construct the receipt using the builder
	 * @return Pointer to the constructed Receipt
	 */
	Receipt* constructReceipt();
	
};

#endif
