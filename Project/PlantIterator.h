#ifndef PLANTITERATOR_H
#define PLANTITERATOR_H

#include "Iterator.h"
class Plant ;

class PlantIterator :public Iterator {


public:
	void first();

	void next();

	void isDone();

	Plant* currentItem();
};

#endif
