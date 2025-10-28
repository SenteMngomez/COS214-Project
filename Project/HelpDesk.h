#ifndef HELPDESK_H
#define HELPDESK_H

#include "Section.h"

class HelpDesk :public Section {

public:
	HelpDesk(std::string name);
	void notify(Person* person);
};

#endif
