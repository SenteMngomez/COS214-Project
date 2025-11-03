#ifndef RECEIPT_H
#define RECEIPT_H

/**
 * @file Receipt.h
 * @brief Representation of a sales receipt containing sold plants and totals.
 *
 * The Receipt class collects sold Plant pointers, tracks the total price and
 * provides both a textual printout and a string representation suitable for
 * returning to callers or persisting.
 *
 * @author Lesedi
 * @date October 30, 2025
 */

#include <string>
#include <iostream>
#include <vector>
#include "Plant.h"
using namespace std;

/**
 * @class Receipt
 * @brief Stores the items and total for a completed sale.
 *
 * Responsibilities:
 * - Keep track of the sold Plant pointers
 * - Track the total sale price
 * - Provide printing and string serialization helpers
 */
class Receipt {

private:
	double totalPrice;        /**< Total price of the receipt (R currency) */
	vector<Plant*> plants;    /**< List of pointers to sold Plant objects */
	string seller;            /**< Name of the seller/store */

public:
	/**
	 * @brief Construct a new, empty Receipt.
	 */
	Receipt();

	/**
	 * @brief Destructor for a Receipt 
	 */
	virtual ~Receipt() = default;

	/**
	 * @brief Set the seller name printed on the receipt.
	 * @param seller The seller/store name
	 */
	void setSeller(string seller);

	/**
	 * @brief Add a sold plant to the receipt.
	 * @param P Pointer to the sold Plant
	 */
	void addPlant(Plant* P);

	/**
	 * @brief Set the total price for the receipt.
	 * @param price Total price in currency units
	 */
	void setTotalPrice(double price);

	/**
	 * @brief Return the receipt formatted as a string.
	 *
	 * @return string A multi-line representation of the receipt suitable for
	 *         logging or sending back to a caller.
	 */
	string toString();  // New method to get receipt as string so it can returned to customer

	/**
	 * @brief Print the receipt to standard output.
	 */
	void print();
};

#endif
