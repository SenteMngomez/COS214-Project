#ifndef MANAGER_H
#define MANAGER_H

#include "Staff.h"

class Manager :public Staff {


public:
	void handleRequest(Person* person);
};

#endif
