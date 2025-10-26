#include "Person.h"

Person::Person(std::string name):name(name){

	messageType="";
	string messageType="";
	string message="";
}

string Person::getName() {
	return name;
}

void Person::sendMessage(string message, string type,std::vector<int>* tags, string decorator) {
	int room=0;

	if(type=="Purchase"){
		room=1;
	}

	this->message=message;
	this->messageType=type;
	this->tags=tags;
	this->decorator=decorator;


	sections[room]->notify(this);

}

string Person::getMessageType() const{
	return this->messageType;
}

string Person::getMessage() const{
	return this->message;
}

std::vector<int>* Person::getTags() {
	return this->tags;
}

std::string Person::getDecorator() const{
	return decorator;
}