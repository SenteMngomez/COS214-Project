#ifndef HELPDESK_H
#define HELPDESK_H

#include "Section.h"

class HelpDesk :public Section {

public:
	Person* personList;

	void notify(Person* person);
};

#endif
