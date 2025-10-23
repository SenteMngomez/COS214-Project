#ifndef GREENHOUSEINTERFACE_H
#define GREENHOUSEINTERFACE_H

#include "InventoryInterface.h"
#include <vector>
#include <algorithm>

class GreenhouseInterface {


public:
	void attach(InventoryInterface* obs);

	void detach(InventoryInterface* obs);

protected:

	std::vector<InventoryInterface*> observers;
	void notify(Plant* plant);
};

#endif 
