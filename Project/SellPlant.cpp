#include "SellPlant.h"
#include "PlantBuilder.h"

SellPlant::SellPlant(PlantBuilder* pb):Command(){
	this->builder = pb;
	sBuild = new SalesAssistance();
	r = nullptr;
}

SellPlant::~SellPlant(){
	if(r != nullptr){
		delete r ;
	}
	if(sBuild != nullptr){
		delete sBuild ;
	}
	if(builder != nullptr){
		delete builder;
	}


}

void SellPlant::setSalesAssitance(SalesAssistance* sa){
    if(sBuild != sa){
        delete sBuild;
        sBuild = sa;
    }
}
void SellPlant::execute(vector<string>* tag, string decorator){
	// cout<<"HII"<<endl;
	vector<Plant*> soldPlants;
	for(string i :*tag){
		if(greenHouse != nullptr){
			Plant* p = greenHouse->removePlant(i);
			if (p) soldPlants.push_back(p);
		}
		cout<<"Initialsed incomplete";
	}

	if(soldPlants.empty()){
		r = nullptr;
		return ;	
	}

    Plant* saleItem = builder->buildCompositePlant(soldPlants, decorator);
	string sellerName = "Green Home"; 
    BasicReceiptBuilder* receiptBuilder = new BasicReceiptBuilder(sellerName, soldPlants);

	// if(sBuild){
	// 	delete sBuild;
	// }
	sBuild->setBuilder(receiptBuilder);
	r = sBuild->constructReceipt();

    std::cout << "Selling " 
              << (soldPlants.size() > 1 ? "group of plants" : "single plant")
              << " from greenhouse " << greenHouse->getName() << std::endl;

	delete receiptBuilder;
	delete saleItem;
}

string SellPlant::getReceipt(){
    if(r){
        return r->toString();
    }
    return "No receipt available";
}

