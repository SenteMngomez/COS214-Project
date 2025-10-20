#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
class Customer :public Person {

public:
	string decorator;

	string getDecorator();
};

#endif
