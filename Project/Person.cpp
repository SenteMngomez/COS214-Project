#include "Person.h"

Person::Person(std::string name):name(name),messageType(""),message(""),tags(nullptr)
,decorator(""){}

Person::~Person(){

	for(Section* section:sections) {
        if(section) section->removePerson(this);
    }
	sections.clear();
}

string Person::getName() {
	return name;
}

void Person::sendMessage(string message, string type,std::vector<string>* tags, string decorator,string sectionName) {

	if(sections.empty()){

		std::cout<<"####"<<name<<" is not in any room ####\n";
		return;
	}

	int room=0;

	if (!sectionName.empty()) {
        for (size_t i = 0; i < sections.size(); i++) {
            if (sections[i]->getName() == sectionName) {
                room = i;
                break;
            }
        }

    }else if(sections.size() >= 2 && (type == "Purchase" || type == "Purchase Complete")) {
        
        for(size_t i=0; i<sections.size(); i++){

            if(sections[i]->getType()=="Sales") {
                room=i;
                break;
            }
        }
    } else {
        for(size_t i=0; i<sections.size(); i++){
            if(sections[i]->getType() != "Sales"){
                room=i;
                break;
            }
        }
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

std::vector<string>* Person::getTags() {
	return this->tags;
}

std::string Person::getDecorator() const{
	return decorator;
}

void Person::addSection(Section* section){
	sections.push_back(section);
}