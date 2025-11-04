#ifndef BASICRECEIPTBUILDER_H
#define BASICRECEIPTBUILDER_H

/**
 * @file BasicReceiptBuilder.h
 * @brief Concrete ReceiptBuilder that assembles a simple receipt from sold plants.
 *
 * This builder implementation creates a Receipt using a provided seller name
 * and a list of sold Plant pointers. It implements the steps required by the
 * ReceiptBuilder interface: add price, add seller and add plant details.
 *
 * @author Lesedi
 * @date October 30, 2025
 */

#include "ReceiptBuilder.h"

#include "Plant.h"
#include <vector>

/**
 * @class BasicReceiptBuilder
 * @brief Minimal implementation of ReceiptBuilder for basic receipts.
 */
class BasicReceiptBuilder : public ReceiptBuilder {
private:
	string sellerName;             /**< Name of the seller to put on the receipt */
	vector<Plant*> soldPlants;     /**< Plants included in the sale */

public:
	/**
	 * @brief Construct a BasicReceiptBuilder with seller name and sold plants.
	 * @param seller Reference to seller name string
	 * @param plants Vector of pointers to sold Plant objects
	 */
	BasicReceiptBuilder(string & seller, vector<Plant*> plants);

	/**
	 * @brief Calculate and set the total price on the receipt.
	 */
	virtual void addPrice();

	/**
	 * @brief Add seller information to the receipt.
	 */
	virtual void addSeller();

	/**
	 * @brief Add plant line-items to the receipt.
	 */
	virtual void addPlantDetails();
};

#endif
