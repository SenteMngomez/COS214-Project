#ifndef STAFF_H
#define STAFF_H

#include "Person.h"

class Staff :public Person {

	private:
		Staff* successor;
	public:
		Staff(std::string name);
		void handleRequest(Person* person);
		virtual void receiveMessage(Person* person, Section* section);
		void setSuccessor(Staff* successor);
};

#endif
