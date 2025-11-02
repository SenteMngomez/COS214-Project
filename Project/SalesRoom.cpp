
#include "SalesRoom.h"

	SalesRoom::SalesRoom(std::string name):Section(name){}

	void SalesRoom::notify(Person* person){

		if(person->getMessageType()=="Purchase Complete"){

			for(Person* p:personList){
				if(p->getName()==person->getDecorator()){
					p->receiveMessage(person,this);
					break;
				}	
			}
			addToHistory(person);
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
