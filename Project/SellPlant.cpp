#include "SellPlant.h"
#include "PlantBuilder.h"

SellPlant::SellPlant(PlantBuilder* pb):Command(){
	this->builder = pb;
	sBuild = nullptr;  
	r = nullptr;
}

SellPlant::~SellPlant(){
	if(r != nullptr){
		delete r ;
	}
	
}

void SellPlant::setSalesAssitance(SalesAssistance* sa){
   
    sBuild = sa;
}
void SellPlant::execute(vector<string>* tag, string decorator){
	

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

    //Build composite/decorated plant first
    Plant* saleItem = builder->buildCompositePlant(soldPlants, decorator);

    //Calculate base plants price before they get reorganized
    double basePlantsPrice = 0.0;
    for(Plant* plant : soldPlants) {
        basePlantsPrice += plant->getPrice();
    }

    //Create receipt
    string sellerName = "Green Home"; 
    BasicReceiptBuilder* receiptBuilder = new BasicReceiptBuilder(sellerName, soldPlants);
    sBuild->setBuilder(receiptBuilder);
    
    //Build basic receipt first
    receiptBuilder->addSeller();
    receiptBuilder->addPlantDetails();
    
    //Get the receipt and modify it to include decorator
    r = receiptBuilder->getReceipt();
    
    
    if(!decorator.empty() && decorator != "none") {
        double decoratorPrice = saleItem->getPrice() - basePlantsPrice;
        string decoratorName = (decorator == "pot") ? "Decorative Pot" : 
                              (decorator == "wrap") ? "Gift Wrap" : decorator;
        r->addPlant(decoratorName, decoratorPrice);
    }
    
    // Set total price from the final sale item
    r->setTotalPrice(saleItem->getPrice());

    std::cout << "Selling " 
              << (soldPlants.size() > 1 ? "group of plants" : "single plant")
              << " from greenhouse " << greenHouse->getName() << std::endl;

	
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

