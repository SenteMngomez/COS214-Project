#include <iostream>
#include <string>

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
#include "SalesClerk.h"
#include "SalesRoom.h"
#include "HelpDesk.h"

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
Staff* createStaffMember(){
    cout<<"please enter your name :";
    string name;
    cin>>name;
    return new Staff(name);


}
void handleSales(){
    
}





using namespace std;





int main() {
    vector<Staff*> staffMembers;

    Greenhouse greenhouse("Green Home");

    FlowerFactory flowerFactory;
    SucculentFactory succulentFactory;
    TreeFactory treeFactory;

    Plant* rose = flowerFactory.createPlant("Rose");
    Plant* cactus = succulentFactory.createPlant("Cactus");
    Plant* oak = treeFactory.createPlant("Oak");

    greenhouse.addPlant(rose);
    greenhouse.addPlant(cactus);
    greenhouse.addPlant(oak);

    greenhouse.showPlants();

    cout<<"Welcome to green home!"<<endl;
    cout<<"Are you a customer or admin ? ";
    string initialPath;
    cin >> initialPath;
    if(initialPath == "") throw "Unable to proceed into green home";
    if(initialPath == "Customer"){
        Customer c = createCustomer();
    }else{
        staffMembers.push_back(createStaffMember());
    }
    


    
    
    
    return 0;

}