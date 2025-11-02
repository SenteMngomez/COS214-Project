#include "Section.h"
#include "Person.h"
#include "Staff.h"
#include <algorithm>

Section::Section(std::string name):name(name){
	admin=nullptr;
}

Section::~Section(){

	personList.clear();
	history.clear();
}

void Section::setAdmin(Staff* admin){

	this->admin=admin;
}

void Section::addPerson(Person* person){

	personList.push_back(person);
}
		
Person* Section::removePerson(Person* person){

	auto it=std::find(personList.begin(), personList.end(), person);
    if (it==personList.end()) return nullptr;
    Person* p=*it;
    personList.erase(it);

    return p;
}

Iterator* Section::createIterator(){
	return new ChatIterator(&history);
}

std::string Section::getHistory() const{

	std::string histOut="========"+name+" history========\n";

	for(std::string m:history){

		histOut+=m+"\n";
	}

	return histOut;
}

std::string Section::getName() const{
	return name;
}

void Section::addToHistory(Person* person){

	if(person->getMessage().empty()){
		return;
	}

	std::string storeMsg=person->getName()+": "+person->getMessage();

	history.push_back(storeMsg);
}