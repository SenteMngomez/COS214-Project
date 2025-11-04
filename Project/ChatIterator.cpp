/**
 * @file ChatIterator.cpp
 * @brief Implementation of the ChatIterator class.
 * @author Mosa Leiee
 * @date 27 October 2025
 */
#include "ChatIterator.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <memory>
using namespace std;

ChatIterator::ChatIterator(const vector<string>* mgs) : messages(mgs ? new vector<string>(*mgs) : nullptr), current(0){
	if (messages){
		sort(messages->begin(), messages->end(), [](const string& a, const string& b){
			auto getType = [](const string& msg){
				istringstream stream(msg);
				string word;
				stream>>word;
				if (!word.empty() && word.back()==':'){
					word.pop_back();
				}
				return word;
			};
			return getType(a) < getType(b);
		});
	}
}

ChatIterator::~ChatIterator(){
	delete messages;
	messages = nullptr;
}

void ChatIterator::first() {
	current = 0;
}

void ChatIterator::next() {
	if (messages && current < messages->size()){
		current++;
	}
}

bool ChatIterator::isDone() {
	return !messages || current >= messages->size();
}

string ChatIterator::currentItem() {
	if (!isDone()){
		return (*messages)[current];
	}
	return {};
}
