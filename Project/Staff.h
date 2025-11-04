#ifndef STAFF_H
#define STAFF_H

#include "Person.h"

/**
 * @file Staff.h
 * @brief Concrete class representing a staff member
 * @author Sente
 * @date October 26, 2025
 */

  /**
  * @class Staff
  * @brief Represents a staff member in the system. Inherits from Person and
  *        provides request handling (Chain of Responsibility) and message receiving.
  */

class Staff :public Person {

	private:
		/// @brief Successor in the chain of responsibility
		Staff* successor;
	public:
		/**
		 * @brief Constructs a Staff with the given name.
		 * @param name The name of the staff member.
		 */
		Staff(std::string name);

		/**
		 * @brief Handles a request sent by a person. If this staff member cannot
		 *        handle the request it should pass it to its successor.
		 * @param person The person who made the request.
		 */
		virtual void handleRequest(Person* person);

		/**
		 * @brief Receives a message from another person sent through a section.
		 *        Implementations should use the provided Person pointer to access
		 *        the sender's message, message type and name via getters.
		 * @param person The sender of the message.
		 * @param section The Section through which the message was delivered.
		 */
		virtual void receiveMessage(Person* person, Section* section);
		 /**
		 * @brief Sets the successor in the chain of responsibility.
		 * @param successor The next Staff handler.
		 */
		void setSuccessor(Staff* successor);
};

#endif
