/**
 * @file ChatIterator.h
 * @brief Declaration of the ChatIterator class.
 * This class implements the Iterator interface to iterate over a collection of chat messages.
 * @author Mosa Leiee
 * @date 27 October 2025
 */

#ifndef CHATITERATOR_H
#define CHATITERATOR_H

#include "Iterator.h"
#include <string>
#include <vector>

using namespace std;
class Section;
/**
 * @class ChatIterator
 * @brief Iterator for chat messages.
 */
class ChatIterator :public Iterator {

private:
	vector<string>* messages; //store messages from person (owned copy so we can sort)
	//Section* section;
	int current;

public:

	/**
	 * @brief Constructor for ChatIterator.
	 * @param messages Vector of chat messages to iterate over. Messages are alphabetically stored based on the request type.
	 */
	ChatIterator(const vector<string>* mgs);
	~ChatIterator();
	//ChatIterator(Section* section);

	/**
	 * @brief Set the iterator to the first chat message.
	 */
	void first() override;

	/**
	 * @brief Move the iterator to the next chat message.
	 */
	void next() override;

	/**
	 * @brief Check if the iterator has reached the end of the chat messages.
	 * @return true if the iterator is done, false otherwise.
	 */
	bool isDone() override;

	/**
	 * @brief Get the current chat message.
	 * @return The current chat message as a string.
	 */
	string currentItem();
};

#endif
