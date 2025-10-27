/**
 * @file ChatIterator.cpp
 * @brief Implementation of the ChatIterator class.
 * @author Mosa Leiee
 * @date 27 October 2025
 */
#include "ChatIterator.h"

ChatIterator::ChatIterator(const vector<string>* mgs) : messages(mgs){
	current = 0;
}
// ChatIterator::ChatIterator(Section* section):section(section){
// 	current = 0;
// }

void ChatIterator::first() {
	current = 0;
}

void ChatIterator::next() {
	if (current < messages->size()){
		current++;
	}
}

bool ChatIterator::isDone() {
	return current >= messages->size();
}

string ChatIterator::currentItem() {
	if (!isDone()){
		return (*messages)[current];
	}
	return "";
}
