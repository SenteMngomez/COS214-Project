/**
 * @file ChatIterator.cpp
 * @brief Implementation of the ChatIterator class.
 * @author Mosa Leiee
 * @date 27 October 2025
 */
#include "ChatIterator.h"

ChatIterator::ChatIterator(const vector<string>& messages){
	chats = messages;
	current = 0;
}

void ChatIterator::first() {
	current = 0;
}

void ChatIterator::next() {
	if (current < chats.size()){
		current++;
	}
}

bool ChatIterator::isDone() {
	return current >= chats.size();
}

string ChatIterator::currentItem() {
	if (!isDone()){
		return chats[current];
	}
	return "";
}
