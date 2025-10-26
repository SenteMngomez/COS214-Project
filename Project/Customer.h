#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
class Customer :public Person {

	public:
		Customer(std::string name);
		virtual void receiveMessage(Person* person, Section* section);
};

#endif
