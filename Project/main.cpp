#include <iostream>
#include <string>
#include <limits>

#include "Plant.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"
#include "TreeFactory.h"
#include "SeedState.h"
#include "Greenhouse.h"
#include "GreenhouseInterface.h"
#include "PlantBuilder.h"
#include "Command.h"
#include "SellPlant.h"
#include "Customer.h"
#include "Person.h"
#include "Staff.h"
#include "Section.h"
#include "Manager.h"
#include "GroundStaff.h"
#include "SalesClerk.h"
#include "SalesRoom.h"
#include "HelpDesk.h"
#include "Command.h"
#include "ConcretePlantBuilder.h"
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
    cout<<"Welcome to greenHome"<<endl;

    Greenhouse greenhouse("Green Home");

    FlowerFactory flowerFactory;
    SucculentFactory succulentFactory;
    TreeFactory treeFactory;
    PlantBuilder* pd = new ConcretePlantBuilder();
    SalesAssistance* sa = new SalesAssistance();  
    SellPlant* saleCommand = new SellPlant(pd);
    saleCommand->setGreenhouse(&greenhouse);
    saleCommand->setSalesAssitance(sa);

    Plant* rose = flowerFactory.createPlant("Rose");
    Plant* cactus = succulentFactory.createPlant("Cactus");
    Plant* oak = treeFactory.createPlant("Oak");

    greenhouse.addPlant(rose);
    greenhouse.addPlant(cactus);
    greenhouse.addPlant(oak);

   int choicePerson;
	
	vector<Section*> rooms;

	SalesClerk* salesMan1=new SalesClerk("Brett Hands");
	Staff* groundsMan1=new GroundStaff("Mick Jagger");
	Manager* manager1=new Manager("Franklin Saint");

    
    salesMan1->setSellPlantCommand(saleCommand);

    

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

    // salesMan1->addSection(help1);
    salesMan1->addSection(sales1);

	rooms.push_back(help1);
	rooms.push_back(sales1);

    cout<<"Please enter option 1 for customer or option 2 if you are part of staff :) ";
    std::cin>>choicePerson;
	if(choicePerson == 1){

		Person* person;

		if(choicePerson==1){

			person=newCustomer(rooms);
		}
        //loop prob goes here 
        //bool flag 
        /*
            while(flag){
            }       
        */
       bool flag = true ;
       while(flag==true){
          clearScreen();

            cout<<"Select next action:\n\t1.View Plants\n\t2.Purchase a plant\n\t3.Ask for help\n";
            int choiceReq;
            cout<<"Enter here: ";
            if(std::cin>>choiceReq){

                if(choiceReq==1){
                    greenhouse.showPlants();
                    cout<<"Select next action:\n\t1.Purchase a plant\n\t2.Ask for help\n\t3.Exit\n";
                    int choiceReq2;
                    cout<<"Enter here: ";
                    if (std::cin>>choiceReq2){

                    
                        if (choiceReq2 == 3){
                            std::cout<<"Thank you visiting GreenHome. Goodbye!"<<endl;
                            return 0;
                        }
                        else if (choiceReq2 == 1|| choiceReq2 == 2){

                            string type=(choiceReq2==1)?"Purchase":"Help";

                            Customer* customer=dynamic_cast<Customer*>(person);

                            if(customer){
                                customerRequest(customer,type);
                            }else{

                                std::cerr << "Error: selected person is not a Customer\n";
                            }

                        }
                    }else{
                        cout<<"Invalid option. Enter 1, 2 or 3";
                    }

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
            cout<<"Need anything else?\n1.Yes \n2.No\n";
			cout<<"Enter here: ";
            int op ;
            cin>>op;
            if(op==1){
                flag = true;
            }else{
                flag = false ;
            }
       }
		
        /*
            as in loop ends here  no need to ask the user anything more :)
        */


        //add the loop to ask if theres anything else 
	}else{
        //adding new plants to the inventory 
        //removing plants from the inventory
        //sending the request to the ground staff ?? how cause the request the could reach manager is in the first if block ??
        //
        cout<< "Welcome back staff member :) hope you are ready to work"<<endl;

	}
   


    
    return 0;
}