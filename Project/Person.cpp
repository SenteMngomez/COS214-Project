#include "Person.h"

Person::Person(std::string name):name(name),messageType(""),message(""),tags(nullptr)
,decorator(""){}

string Person::getName() {
	return name;
}

void Person::sendMessage(string message, string type,std::vector<int>* tags, string decorator) {

	if(sections.empty()){

		std::cout<<"####"<<name<<" is not in any room ####";
		return;
	}

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

void Person::addSection(Section* section){
	sections.push_back(section);
}