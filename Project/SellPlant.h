#ifndef SELLPLANT_H
#define SELLPLANT_H

/**
 * @file SellPlant.h
 * @brief Command used to sell one or more plants and generate a receipt.
 *
 * The SellPlant command removes plants from the greenhouse inventory (via
 * Greenhouse interfaces), constructs a composite plant when needed, and uses
 * a ReceiptBuilder/SalesAssistance to produce a Receipt object.
 *
 * @author Lesedi
 * @date October 30, 2025
 */

#include "Command.h"
#include "Inventory.h"
#include "SalesAssistance.h"
#include "BasicReceiptBuilder.h"

#include <string>
#include <vector>

#include <iostream>
using namespace std;
class PlantBuilder;

/**
 * @class SellPlant
 * @brief Concrete Command that handles selling plants and building receipts.
 *
 * Usage:
 * - Construct with a PlantBuilder implementation
 * - Configure with setGreenhouse() and setSalesAssitance()
 * - Call execute(tagList, decorator) to perform the sale
 * - Optionally call getReceipt() to retrieve the textual receipt
 */
class SellPlant : public Command {
private:
	PlantBuilder* builder;        /**< Builder used to create composite items */
	SalesAssistance* sBuild;      /**< Helper that drives the ReceiptBuilder */
	Receipt* r;                   /**< Last generated receipt (owned elsewhere) */

public:
	/**
	 * @brief Construct a SellPlant command with the provided PlantBuilder.
	 * @param pb Pointer to a PlantBuilder used to assemble composite plants
	 */
	SellPlant(PlantBuilder* pb);

	/**
	 * @brief Deletes receipt
	 */
	~SellPlant();

	/**
	 * @brief Set the SalesAssistance helper used to build receipts.
	 * @param sBuild Pointer to a SalesAssistance instance
	 */
	void setSalesAssitance(SalesAssistance* sBuild);

	/**
	 * @brief Get the last generated receipt as a string.
	 *
	 * Returns a multi-line receipt string if a sale has been performed,
	 * otherwise returns a message indicating no receipt is available.
	 *
	 * @return string Formatted receipt text or an informative message
	 */
	string getReceipt();

	/**
	 * @brief Execute the sell command for the provided plant tag(s).
	 * @param tag Pointer to a vector of plant tag ids to sell
	 * @param decorator Optional decorator type (e.g., "wrap" or "pot")
	 */
	virtual void execute(vector<string>* tag, string decorator = "");
};

#endif
