/**
 * @file Person.h
 * @brief Abstract base class representing a person
 * @author Sente
 * @date October 26, 2025
 */

#ifndef PERSON_H
#define PERSON_H

#include "Section.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/**
 * @class Person
 * @brief Abstract base class representing a person.
 * Provides common attrributes and methods for customers and staff
 */

class Person {

private:
	std::vector<Section*> sections;
	string name;
	string messageType;
	string message;
	std::vector<int>* tags;
	std::string decorator;

public:
	Person(std::string name);

	/**
	 * @brief Gives access to name attribute
	 * @return name
	 */
	string getName();

	/**
	 * @brief Stores attribute in object and calls Section's notify function with this as the parameter, in order to send a message/make a request through the Section chat
	 * @param message The message being sent
	 * @param type The type of message/request being sent
	 * @param tags A vector that stores the tags of plants to be purchased/cared for. Optional
	 * @param decorator The type of decorator that a customer wants to add to their plant(s) when purchasing. Optional
	 */
	virtual void sendMessage(string message, string type, std::vector<int>* tags=nullptr, string decorator="",string sectionName="");

	/**
	 * @brief Receives a message from another person sent through a section
	 * @param message The message being received
	 * @param person The person who sent the message beibng received. Uses getters to retrieve message, messageType and name
	 */
	virtual void receiveMessage(Person* person, Section* section)=0;

	/**
	 * @brief Gives access to messageType attribute
	 * @return messageType
	 */
	string getMessageType() const;

	/**
	 * @brief Gives access to message attribute
	 * @return message
	 */
	string getMessage() const;

	/**
	 * @brief Gives access to decorator attribute
	 * @return decorator
	 */
	string getDecorator() const;

	/**
	 * @brief Gives access to tags attribute
	 * @return tags
	 */
	std::vector<int>* getTags();

	void addSection(Section* section);

};

#endif
