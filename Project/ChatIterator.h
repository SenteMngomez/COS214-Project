#ifndef CHATITERATOR_H
#define CHATITERATOR_H

#include "Iterator.h"
#include <string>

using namespace std;
class ChatIterator :public Iterator {


public:
	void first();

	void next();

	void isDone();

	string currentItem();
};

#endif
