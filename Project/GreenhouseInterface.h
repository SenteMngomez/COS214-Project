#ifndef GREENHOUSEINTERFACE_H
#define GREENHOUSEINTERFACE_H

#include "InventoryInterface.h"

class GreenhouseInterface {


public:
	void attach(InventoryInterface* obs);

	void detach(InventoryInterface* obs);

protected:
	void notify(Plant* plant);
};

#endif
