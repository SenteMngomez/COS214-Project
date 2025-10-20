#ifndef SECTION_H
#define SECTION_H


#include "Iterator.h"
class Person;


class Section {

public:
	virtual void notify(Person* person) = 0;

	Iterator* createIterator();
};

#endif
