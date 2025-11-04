#ifndef RECEIPT_H
#define RECEIPT_H

/**
 * @file Receipt.h
 * @brief Representation of a sales receipt containing sold plants and totals.
 *
 * The Receipt class collects sold Plant information, tracks the total price and
 * provides both a textual printout and a string representation suitable for
 * returning to callers or persisting.
 *
 * @author Lesedi
 * @date October 30, 2025
 */

#include <string>
#include <iostream>
#include <vector>
using namespace std;

/**
 * @struct PlantInfo
 * @brief Holds plant information for receipt storage
 */
struct PlantInfo {
    string type;
    double price;
    
    PlantInfo(const string& t, double p) : type(t), price(p) {}
};

/**
 * @class Receipt
 * @brief Stores the items and total for a completed sale.
 *
 * Responsibilities:
 * - Keep track of the sold Plant information 
 * - Track the total sale price
 * - Provide printing and string serialization helpers
 */
class Receipt {

private:
	double totalPrice;           /**< Total price of the receipt (R currency) */
	vector<PlantInfo> plants;    /**< List of sold Plant information */
	string seller;               /**< Name of the seller/store */

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
	 * @param type The type of the plant
	 * @param price The price of the plant
	 */
	void addPlant(const string& type, double price);

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
