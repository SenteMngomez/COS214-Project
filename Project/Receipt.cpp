#include "Receipt.h"

Receipt::Receipt() {
	// TODO - implement Receipt::Receipt
	this->totalPrice = 0.0;
}

void Receipt::print() {
	// TODO - implement Receipt::print
	 cout << "\n------ NURSERY RECEIPT ------" << endl;
        cout << "Seller: " << seller << endl;
        cout << "Items:" << endl;
        for (size_t i = 0; i < plants.size(); ++i) {
            cout << "  - " << plants[i]->getType()
                 << " (R" << plants[i]->getPrice() << ")" << endl;
        }
        cout << "-----------------------------" << endl;
        cout << "Total: R" << totalPrice << endl;
        cout << "-----------------------------" << endl;
    
	
}

void Receipt::setSeller(string seller){
	this->seller = seller;
}

void Receipt::setTotalPrice(double price){
	this->totalPrice = price ;
}

void Receipt::addPlant(Plant* p){
	plants.push_back(p);
}