#ifndef MANAGER_H
#define MANAGER_H

#include "Staff.h"

class Manager :public Staff {

	public:
		Manager(std::string name);
		void handleRequest(Person* person);
};

#endif
