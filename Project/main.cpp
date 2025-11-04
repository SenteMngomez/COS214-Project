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
#include "MatureState.h"
#include "SproutState.h"
#include "SeedState.h"
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

		cout<<"Please enter the tags of the plants you would like (Type s to finish):\n";

		std::string tag;
		vector<std::string> tags;

		while(true){
            cout<<"Tag: ";
            if(!(std::cin>>tag)){
                
                cout<<"Invalid input. Please enter a valid tag (or s to finish)."<<endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            if(tag=="s")break;
            tags.push_back(tag);
        }

		int decorate;
		cout<<"Would you like your plants in:\n\t1.Wrap(+R6.00)\n\t2.Flower Pot(+R10.00)\n\t3.None\n";
		cout<<"Enter here: ";
		std::cin>>decorate;

		if(decorate==1||decorate==2){
			
			string decorator=(decorate==1)?"wrap":"pot";

			customer->sendMessage(message,type,&tags,decorator);

		}else{
			customer->sendMessage(message,type,&tags);
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

void handleCarePlant(Manager* manager,string Type){/*calls the ground stuff through the mediator
                                                    to handle the plants that need to be cared for */ 
    
    string message;
	cout<<"Please enter the message for your  request: ";
	std::getline(std::cin>>std::ws, message);

    

    cout<<"Please enter the tags of the plants you would like to care for (Type s to finish):\n";

    std::string tag;
    vector<std::string> tags;

    while(true){
        cout<<"Tag: ";
        if(!(std::cin>>tag)){
            
            cout<<"Invalid input. Please enter a valid tag (or s to finish)."<<endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        if(tag=="s")break;
        tags.push_back(tag);
    }

    manager->sendMessage(message,Type,&tags);
}

int main() {
    string password = "StartingFive";
    cout<<"Welcome to greenHome"<<endl;

    Greenhouse greenhouse("Green Home");
	Inventory* inventory=Inventory::instance();

	greenhouse.attach(inventory);

    FlowerFactory flowerFactory;
    SucculentFactory succulentFactory;
    TreeFactory treeFactory;

    PlantBuilder* pd = new ConcretePlantBuilder();
    SalesAssistance* sa = new SalesAssistance();  
    SellPlant* saleCommand = new SellPlant(pd);
	WaterPlant* waterCommand= new WaterPlant();
	GiveSunlight* sunlightCommand=new GiveSunlight();

	waterCommand->setGreenhouse(&greenhouse);
	sunlightCommand->setGreenhouse(&greenhouse);
    saleCommand->setGreenhouse(&greenhouse);
    saleCommand->setSalesAssitance(sa);

    Plant* rose = flowerFactory.createPlant("Rose");
    Plant* cactus = succulentFactory.createPlant("Cactus");
    Plant* oak = treeFactory.createPlant("Oak");
	Plant* tulip= flowerFactory.createPlant("Tulip","Blue");

	cactus->setState(new MatureState());
	tulip->setState(new MatureState());

    greenhouse.addPlant(rose);
    greenhouse.addPlant(cactus);
    greenhouse.addPlant(oak);
	greenhouse.addPlant(tulip);

	
	//Adding more plants to greenhouse using prototype
	for(int i=0;i<3;i++){

		greenhouse.addPlant(rose->clone());
		greenhouse.addPlant(tulip->clone());
	}

	SalesClerk* salesMan1=new SalesClerk("Brett Hands");
	GroundStaff* groundsMan1=new GroundStaff("Mick Jagger");
	Manager* manager1=new Manager("Franklin Saint");

	groundsMan1->setGiveSunlightCommand(sunlightCommand);
	groundsMan1->setWaterPlantCommand(waterCommand);
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

    manager1->addSection(help1);

    salesMan1->addSection(help1);
    salesMan1->addSection(sales1);

	vector<Section*> rooms;

	rooms.push_back(help1);
	rooms.push_back(sales1);

	int choicePerson;

	Person* person = nullptr;

    cout<<"Please enter option 1 for customer or option 2 if you are part of staff :) ";
    std::cin>>choicePerson;
	if(choicePerson == 1){

		person=newCustomer(rooms);
	
       bool flag = true ;
       while(flag==true){
          clearScreen();

            cout<<"Select next action:\n\t1.View Plants\n\t2.Purchase a plant\n\t3.Ask for help\n";
            int choiceReq;
            cout<<"Enter here: ";
            if(std::cin>>choiceReq){

                if(choiceReq==1){
                    greenhouse.showOrderedPlants();
                    cout<<"Select next action:\n\t1.Purchase a plant\n\t2.Ask for help\n\t3.Exit\n";
                    int choiceReq2;
                    cout<<"Enter here: ";
                    if (std::cin>>choiceReq2){

                        if (choiceReq2 == 3){
                            std::cout<<"Thank you visiting GreenHome. Goodbye!"<<endl;
                            flag=false;
							break;
                        }
                        else if (choiceReq2 == 1|| choiceReq2 == 2){

                            string type=(choiceReq2==1)?"Purchase":"Help";

							if(type=="Purchase") greenhouse.showOrderedPlants();

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
		
       
	}else if(choicePerson==2){

		bool flag = true ;
		
        cout<<"Enter Password: ";
        string enteredPassword;
        cin>>enteredPassword;
        
            if(enteredPassword != password){
				cout<<"Incorrect password"<<endl;
                flag=false;
            }
        
        if(flag){
        	clearScreen();
        	cout<< "Welcome back staff member :) hope you are ready to work"<<endl;
		 }

        while(flag == true){

            cout<<"\t1.Care For Plant(s)\n\t2.Add Plant \n\t3.Remove Plant(s)\n\t4.View Plants\n\t5.Progress Plants\n\t6.Rooms\n\t7.View Ordered Plants\n\t8.Send Message\n\t9.Exit\n\t"<<endl;
            int op2;
            cout<<"What will we be doing today?\n";
			cout<<"Enter here: ";
            cin>>op2;
            if(op2==1){
                string type="Care";
                greenhouse.showPlants();
                handleCarePlant(manager1,type);
            }else if(op2 == 2){
                //figure out the plant to add 
                cout<<"Please select what you would like to add:\n\t1.Flower\n\t2.Tree\n\t3.Succulent\n";
				cout<<"Enter here: ";
                int option;
                cin>>option;
                if(option == 1){
					int typeInt;
                    string type;
                    cout<<"What type of flower do you want to add:\n\t1.Rose\n\t2.Tulip\n";
                    std::cin>>typeInt;

					if(typeInt==1){

						type="Rose";
					}else if(typeInt==2){
						type="Tulip";
					}else{
						cout<<"Invalid input.";
						break;
					}

					cout<<"What colour is this "<<type<<": ";
                	string col;
                	cin>>col;

					Plant* adding=nullptr;

						if(!col.empty()){

							adding = flowerFactory.createPlant(type,col);
						}else{

							adding = flowerFactory.createPlant(type);
						}

					cout<<"How mature is the "<<type<<": ";
					cout<<"\n\t1.Seed\n\t2.Sprout\n\t3.Mature\n";

					int maturity=0;
                	cin>>maturity;

					if(maturity==1){

					}else if(maturity==2){

						adding->setState(new SproutState());
					}else if(maturity==3){

						adding->setState(new MatureState());
					}else{

						cout<<"Invalid input."<<endl;

					}

 
					if(adding){
						greenhouse.addPlant(adding);
                    	cout<<"A "<<type<<" has been added to the greenhouse";
						adding->print();
					}else{
						cout<<"No seeds are available for "<<type<<" at the moment\n";
					}
                    
                }else if(option==2){
                    int typeInt;
                    string type;
                    cout<<"What type of tree do you want to add:\n\t1.Oak\n\t2.Mango\n";
                    std::cin>>typeInt;

					if(typeInt==1){

						type="Oak";
					}else if(typeInt==2){
						type="Mango";
					}else{
						cout<<"Invalid input.";
						break;
					}

					cout<<"What colour is this "<<type<<": ";
                	string col;
                	cin>>col;

					Plant* adding=nullptr;

						if(!col.empty()){

							adding = treeFactory.createPlant(type,col);
						}else{

							adding = treeFactory.createPlant(type);
						}

					cout<<"How mature is the "<<type<<": ";
					cout<<"\n\t1.Seed\n\t2.Sprout\n\t3.Mature\n";

                	int maturity=0;
                	cin>>maturity;

					if(maturity==1){

					}else if(maturity==2){

						adding->setState(new SproutState());
					}else if(maturity==3){

						adding->setState(new MatureState());
					}else{

						cout<<"Invalid input."<<endl;

					}
 
					if(adding){
						greenhouse.addPlant(adding);
                    	cout<<"A "<<type<<" has been added to the greenhouse";
						adding->print();
					}else{
						cout<<"No seeds are available for "<<type<<" at the moment\n";
					}

                }else if(option==3){
                    int typeInt;
                    string type;
                    cout<<"What type of tree do you want to add:\n\t1.Begonia\n\t2.Cactus\n";
                    std::cin>>typeInt;

					if(typeInt==1){

						type="Begonia";
					}else if(typeInt==2){
						type="Cactus";
					}else{
						cout<<"Invalid input.";
						break;
					}

					cout<<"What colour is this "<<type<<": ";
                	string col;
                	cin>>col;

					Plant* adding=nullptr;

						if(!col.empty()){

							adding = succulentFactory.createPlant(type,col);
						}else{

							adding = succulentFactory.createPlant(type);
						}

					cout<<"How mature is the "<<type<<": ";
					cout<<"\n\t1.Seed\n\t2.Sprout\n\t3.Mature\n";

					int maturity=0;
                	cin>>maturity;

					if(maturity==1){

					}else if(maturity==2){

						adding->setState(new SproutState());
					}else if(maturity==3){

						adding->setState(new MatureState());
					}else{

						cout<<"Invalid input."<<endl;

					}
 
					if(adding){
						greenhouse.addPlant(adding);
                    	cout<<"A "<<type<<" has been added to the greenhouse";
						adding->print();
					}else{
						cout<<"No seeds are available for "<<type<<" at the moment\n";
					}

                }
            }else if(op2==3){
                clearScreen();
                greenhouse.showPlants();
                cout<<"Which plant(s) will you be removing from the greenhouse\n"<<endl;
                cout<<"Please enter the tags of the plants you would like to remove (Type s to finish):\n";

                std::string tag;
                vector<std::string> tags;

                while(true){
                    cout<<"Tag: ";
                    if(!(std::cin>>tag)){
                        
                        cout<<"Invalid input. Please enter a valid tag (or s to finish)."<<endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        continue;
                    }
                    if(tag=="s")break;
                    tags.push_back(tag);
                }

                for(std::string i : tags){
					Plant* removedPlant=greenhouse.removePlant(i);
                    if(removedPlant){

						cout<<"Successfully removed Plant-"<<i<<"\n";
						delete removedPlant;
					}else{

						cout<<"Unable to remove Plant-"<<i<<"\n";
					}
                }
                
            }else if(op2==4){
				clearScreen();
                greenhouse.showPlants();

			}else if(op2==5){

				cout<<"Progressing plants in greenhouse-"<<greenhouse.getName()<<"\n---------------------------------"<<endl;

				greenhouse.progressPlants();

				cout<<"\n";

			}else if(op2==6){

				cout<<"\t1.View "<<help1->getName()<<"\n\t2.View "<<sales1->getName()<<"\n";

				int roomOp;
				cout<<"Enter here: ";

				if(std::cin>>roomOp){
					
					if(roomOp==1){
						cout<<help1->getHistory();
					}else if(roomOp==2){
						cout<<sales1->getHistory();
					}else{
						cout<<"Invalid option.";
					}
                }

			}else if(op2==7){

				greenhouse.showOrderedPlants();

			}else if(op2==8){

				cout<<"Enter the message you would like to send: ";
				string message;
				std::getline(std::cin>>std::ws, message);

				manager1->sendMessage(message,"Help");

			}else if(op2==9){

				flag=false;
			}else{

				cout<<"Invalid input."<<endl;
				
			}
          
            cout<<"\nNeed anything else?\n\t1.Yes \n\t2.No\n";
			cout<<"Enter Here: ";
            int op ;
            cin>>op;
            if(op==1){
                flag = true;
            }else{
                flag = false ;
            }
        }

	}else{

		cout<<"Invalid input. Please enter 1 or 2";
	}
   
	greenhouse.detach(inventory);

	if(person){

		for(Section* section:rooms){
			section->removePerson(person);
		}
		delete person;
	}

	help1->removePerson(salesMan1);
	help1->removePerson(groundsMan1);
	help1->removePerson(manager1);
	sales1->removePerson(manager1);
	sales1->removePerson(salesMan1);

	delete salesMan1;
    delete groundsMan1;
    delete manager1;

	delete help1;
    delete sales1;

	delete waterCommand;
	delete sunlightCommand;
	delete saleCommand;

	delete pd;
	delete sa;

	//inventory->clearInventory();

    delete inventory;

    return 0;
}