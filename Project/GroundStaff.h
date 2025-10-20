#ifndef GROUNDSTAFF_H
#define GROUNDSTAFF_H

#include "Staff.h"
#include "Greenhouse.h"


class GroundStaff :public Staff {


public:
	void handleRequest(Person* person);

	void careForPlant(int* tag);

	void addPlant(Greenhouse* greenHouse, string type);
};

#endif
