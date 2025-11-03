#include "HelpDesk.h"

HelpDesk::HelpDesk(std::string name):Section(name){
	type="Help";
}

void HelpDesk::notify(Person* person){

	if(person->getMessageType()=="Purchase"||person->getMessageType()=="Purchase Complete"){

		std::cout<<"Cannot send "<<person->getMessageType()<<" message in "<<type<<" room\n";
		return;
	}
	
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
