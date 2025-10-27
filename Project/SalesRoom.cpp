
#include "SalesRoom.h"

	SalesRoom::SalesRoom(std::string name):Section(name){}

	// void SalesRoom::notify(Person* person){

	// 	for(Person* p:personList){

	// 		p->receiveMessage(person,this);
	// 	}

	// 	if(admin){
	// 		admin->handleRequest(person);
	// 		return;
	// 	}
		
	// 	for(Person* p:personList){
	// 		Staff* staff=dynamic_cast<Staff*>(p);
	// 		if (staff){
	// 			staff->handleRequest(person);
	// 			break;
	// 		}
	// 	}
	// }
