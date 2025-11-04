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
            cout << "  - " << plants[i].type
                 << " (R" << plants[i].price << ")" << endl;
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

void Receipt::addPlant(const string& type, double price){
	plants.push_back(PlantInfo(type, price));
}

string Receipt::toString(){
    string result;
    result += "\n------ NURSERY RECEIPT ------\n";
    result += "Seller: " + seller + "\n";
    result += "Items:\n";
    for(size_t i = 0; i < plants.size(); ++i){
        result += "  - " + plants[i].type + 
                 " (R" + to_string(plants[i].price) + ")\n";
    }
    result += "-----------------------------\n";
    result += "Total: R" + to_string(totalPrice) + "\n";
    result += "-----------------------------\n";
    return result;
}