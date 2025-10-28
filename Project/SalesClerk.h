#ifndef SALESCLERK_H
#define SALESCLERK_H

#include "Staff.h"


#include <string>
#include "SellPlant.h"
using namespace std;
class SalesClerk : public Staff {


public:
	void handleRequest(Person* person);

	void purchaseComplete(std::string msg);

	void setSellPlantCommannd(SellPlant* sellPlantCommand);

private:
	SellPlant* sellPlantCommand;
	void sell(std::vector<int>* tags, string decorator);
};

#endif
