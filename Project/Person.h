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
	/// @brief Sections the person is part of
	std::vector<Section*> sections;
	/// @brief Name of the person
	string name;
	/// @brief Type of the message/request being sent
	string messageType;
	/// @brief The message being sent
	string message;
	/// @brief Tags of plants to be purchased/cared for
	std::vector<string>* tags;
	/// @brief Type of decorator for plant purchase
	std::string decorator;

public:
	/**
	 * @brief Constructs a Person with the given name.
	 * @param name The name of the person.
	 */
	Person(std::string name);

	/**
	 * @brief Destroys the Person and releases any runtime resources.
	 */
	virtual ~Person();

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
	virtual void sendMessage(string message, string type, std::vector<string>* tags=nullptr, string decorator="",string sectionName="");

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
	std::vector<string>* getTags();

	/**
	 * @brief Adds a Section to the person's list of sections
	 * @param section Pointer to the Section to add
	 */
	void addSection(Section* section);

};

#endif
