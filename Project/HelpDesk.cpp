#include "HelpDesk.h"

HelpDesk::HelpDesk(std::string name):Section(name){

	
}

void HelpDesk::notify(Person* person){
	
	for(Person* p:personList){
			if(p==person) continue;
			p->receiveMessage(person,this);
		}

		addToHistory(person);

		if(admin){
			admin->handleRequest(person);
			return;
		}
		
		for(Person* p:personList){
			Staff* staff=dynamic_cast<Staff*>(p);
			if (staff){
				staff->handleRequest(person);
				break;
			}
		}
}
