#include "Person.h"

string Person::getName() {
	// TODO - implement Person::getName
	throw "Not yet implemented";
}

void Person::sendMessage(string message, string type, int* tags, string decorator) {
	// TODO - implement Person::sendMessage
	throw "Not yet implemented";
}

void Person::receiveMessage(Person* person) {
	// TODO - implement Person::receiveMessage
	throw "Not yet implemented";
}

string Person::getMessageType() {
	return this->messageType;
}

string Person::getMessage() {
	return this->message;
}

int* Person::getTag() {
	return this->tag;
}
