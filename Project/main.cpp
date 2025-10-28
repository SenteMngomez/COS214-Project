#include <iostream>
#include <string>
#include <limits>
#include "Plant.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"
#include "TreeFactory.h"
#include "SeedState.h"
#include "Greenhouse.h"
#include "Customer.h"
#include "GroundStaff.h"
#include "Manager.h"
#include "SalesClerk.h"
#include "SalesRoom.h"
#include "HelpDesk.h"

using namespace std;

Customer* newCustomer(vector<Section*> sections){

	cout<<"Please enter your name: ";
	string name;

	std::getline(std::cin>>std::ws, name);
	cout<<"\nWelcome, "<<name<<"!\n";

	Customer* nCustomer=new Customer(name);

	for(Section* s:sections){

		s->addPerson(nCustomer);
		nCustomer->addSection(s);
	}

	return nCustomer;
}

void customerRequest(Customer* customer,string type){

	string message;
	cout<<"Please enter the message for your "<<type<<" request: ";
	std::getline(std::cin>>std::ws, message);

	if(type=="Purchase"){

		cout<<"Please enter the tags of the plants you would like (Type -1 to finish):\n";

		int tag;
		vector<int>* tags=new vector<int>();

		while(true){
            cout<<"Tag: ";
            if(!(std::cin>>tag)){
                
                cout<<"Invalid input. Please enter a valid tag (or -1 to finish)."<<endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            if(tag==-1)break;
            tags->push_back(tag);
        }

		int decorate;
		cout<<"Would you like your plants in:\n\t1.Wrap\n\t2.Flower Pot\n\t3.None\n";
		cout<<"Enter here: ";
		std::cin>>decorate;

		if(decorate==1||decorate==2){
			
			string decorator=(decorate==1)?"wrap":"pot";

			customer->sendMessage(message,type,tags,decorator);

		}else{
			customer->sendMessage(message,type,tags);
		}
		
	}else if(type=="Help"){

		customer->sendMessage(message,type);
	}else{

		cout<<"Invalid request type\n";
	}

}

void clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

int main() {

	cout<<"=========GreenGreenGreen=========\nAre you a:\n\t1.Customer\n\t2.Admin\n";
	int choicePerson;
	
	vector<Section*> rooms;

	Staff* salesMan1=new SalesClerk("Brett Hands");
	Staff* groundsMan1=new GroundStaff("Mick Jagger");
	Manager* manager1=new Manager("Franklin Saint");

	manager1->setSuccessor(salesMan1);
	salesMan1->setSuccessor(groundsMan1);

	HelpDesk* help1=new HelpDesk("Help-A");
	SalesRoom* sales1=new SalesRoom("Sales-A");

	help1->addPerson(salesMan1);
	help1->addPerson(groundsMan1);
	help1->addPerson(manager1);

	help1->setAdmin(manager1);

	sales1->addPerson(manager1);
	sales1->addPerson(salesMan1);

	rooms.push_back(help1);
	rooms.push_back(sales1);

	if(std::cin>>choicePerson){

		Person* person;

		if(choicePerson==1){

			person=newCustomer(rooms);
		}

		clearScreen();

		cout<<"Select next action:\n\t1.View Plants\n\t2.Purchase a plant\n\t3.Ask for help\n";
		int choiceReq;
		cout<<"Enter here: ";
		if(std::cin>>choiceReq){

			if(choiceReq==1){

			}else if(choiceReq==2||choiceReq==3){

				string type=(choiceReq==2)?"Purchase":"Help";

				Customer* customer=dynamic_cast<Customer*>(person);

				if(customer){
					customerRequest(customer,type);
				}else{

					std::cerr << "Error: selected person is not a Customer\n";
				}

			}
		}

	}else{

		cout<<"Invalid option. Enter 1 or 2.";
	}
    
    return 0;
}