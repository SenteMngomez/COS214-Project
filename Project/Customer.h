#ifndef CUSTOMER_H
#define CUSTOMER_H

/**
 * @file Customer.h
 * @brief Concrete class representing a customer
 * @author Sente
 * @date October 26, 2025
 *
 * @class Customer
 * @brief Represents a customer in the system. Inherits from Person and implements
 *        behaviour for receiving messages sent through a Section.
 */

#include "Person.h"
class Customer :public Person {

	public:
		/**
         * @brief Constructs a Customer with the given name.
         * @param name The name of the customer.
         */
		Customer(std::string name);
		/**
         * @brief Handles receiving a message from another Person via a Section.
         *        Implementations should use the provided Person pointer to access
         *        the sender's message, message type and name via getters.
         * @param person The sender of the message.
         * @param section The Section through which the message was delivered.
         */
		virtual void receiveMessage(Person* person, Section* section);
};

#endif
