#ifndef PERSON_H
#define PERSON_H

#include "Section.h"
#include <string>
using namespace std;
class Person {

private:
	Section** sections;
	string name;
	string messageType;
	string message;
	int* tag;

public:
	string getName();

	void sendMessage(string message, string type, int* tags=nullptr, string decorator="");

	void receiveMessage(Person* person);

	string getMessageType();

	string getMessage();

	int* getTag();

	//add destructor 
};

#endif
