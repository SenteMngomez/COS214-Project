#ifndef SALESCLERK_H
#define SALESCLERK_H

#include "Staff.h"


#include <string>
using namespace std;
class SalesClerk : public Staff {


public:
	void handleRequest(Person* person);

	void sell(int* tag, string decorator);

	void purchaseComplete(int string);
};

#endif
