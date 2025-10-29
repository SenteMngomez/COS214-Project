#ifndef SALESCLERK_H
#define SALESCLERK_H

#include "Staff.h"
#include <string>
#include "SellPlant.h"

/**
 * @file SalesClerk.h
 * @brief Concrete class representing a sales clerk (specialised Staff)
 * @author Sente
 * @date October 26, 2025
 */
using namespace std;

/**
 * @class SalesClerk
 * @brief Represents a sales clerk in the system. Inherits from Staff and
 *        handles Purchase requests and executes SellPlant commands.
 */
class SalesClerk : public Staff {

	public:
		SalesClerk(string name):Staff(name){}

		SalesClerk(std::string name);

		/**
		 * @brief Handles a request sent by a person. SalesClerk will handle
		 *        requests of type "Purchase"; otherwise it should delegate to the
		 *        base Staff handler.
		 * @param person The person who made the request.
		 */
		void handleRequest(Person* person);

		/**
		 * @brief Callback invoked when a purchase is complete to notify others.
		 * @param msg Message describing the purchase completion.
		 */
		void purchaseComplete(std::string msg);

		/**
		 * @brief Sets the SellPlant command used to perform sales.
		 * @param sellPlantCommand Pointer to a SellPlant command object.
		 */
		void setSellPlantCommand(SellPlant* sellPlantCommand);

	private:
		
		SellPlant* sellPlantCommand;

		/**
		 * @brief Performs the sale using provided plant tags and decorator.
		 * @param tags Vector of plant tag IDs to sell.
		 * @param decorator The decorator to apply to sold plants.
		 */
		void sell(std::vector<int>* tags, string decorator);
};

#endif
