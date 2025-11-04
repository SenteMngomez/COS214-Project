#include "SellPlant.h"
#include "PlantBuilder.h"

SellPlant::SellPlant(PlantBuilder* pb):Command(){
	this->builder = pb;
	sBuild = nullptr;  // Don't create one - will be set externally
	r = nullptr;
}

SellPlant::~SellPlant(){
	if(r != nullptr){
		delete r ;
	}
	// Don't delete sBuild - it's externally managed via setSalesAssitance
	// Don't delete builder - it's externally managed (passed in constructor)
}

void SellPlant::setSalesAssitance(SalesAssistance* sa){
    // Simply set the pointer - don't delete anything since we don't own sBuild
    sBuild = sa;
}
void SellPlant::execute(vector<string>* tag, string decorator){
	// cout<<"HII"<<endl;

	if(!tag || !greenHouse || !sBuild) {
        cout << "Invalid parameters for plant sale" << endl;
        return;
    }

	vector<Plant*> soldPlants;
	for(string i :*tag){
		Plant* p = greenHouse->removePlant(i);
        if (p) {
            soldPlants.push_back(p);
        } else {
            cout << "Plant not found: " << i << endl;
        }
	}

	if(soldPlants.empty()){
		cout << "No plants found to sell" << endl;
		r = nullptr;
		return ;	
	}

    // Create receipt with the plants BEFORE building the composite
    // This ensures Receipt gets valid pointers before they're reorganized
	string sellerName = "Green Home"; 
    BasicReceiptBuilder* receiptBuilder = new BasicReceiptBuilder(sellerName, soldPlants);
	sBuild->setBuilder(receiptBuilder);
	r = sBuild->constructReceipt();

    // Build composite/decorated plant - this will take ownership of the plants
    Plant* saleItem = builder->buildCompositePlant(soldPlants, decorator);

    std::cout << "Selling " 
              << (soldPlants.size() > 1 ? "group of plants" : "single plant")
              << " from greenhouse " << greenHouse->getName() << std::endl;

	// Clean up the sale item - this will clean up all the individual plants too
	if(saleItem) {
        delete saleItem;
    }
}

string SellPlant::getReceipt(){
    if(r){
        return r->toString();
    }
    return "No receipt available";
}

