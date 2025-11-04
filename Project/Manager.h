#ifndef MANAGER_H
#define MANAGER_H

#include "Staff.h"

/**
 * @file Manager.h
 * @brief Concrete class representing a manager (specialised Staff)
 * @author Sente
 * @date October 26, 2025
 */

 /**
 * @class Manager
 * @brief Represents a manager in the system. Inherits from Staff and handles
 *        requests that require managerial attention.
 */
class Manager :public Staff {

	public:
		/**
         * @brief Constructs a Manager with the given name.
         * @param name The name of the manager.
         */
		Manager(std::string name);

		/**
         * @brief Handles a request sent by a person. Manager will handle requests
         *        of type "Help"; otherwise it should delegate to the base Staff
         *        handler.
         * @param person The person who made the request.
         */
		void handleRequest(Person* person);
};

#endif
