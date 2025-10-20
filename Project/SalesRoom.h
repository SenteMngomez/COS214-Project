#ifndef SALESROOM_H
#define SALESROOM_H

#include "Section.h"

class SalesRoom :public Section {

public:
	Person* personList;

	void notify(Person* person);
};

#endif
