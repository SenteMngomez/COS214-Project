#ifndef RECEIPT_H
#define RECEIPT_H

#include <string>
#include <iostream>
#include <vector>
#include "Plant.h"
using namespace std;

class Receipt {

private:
	double totalPrice;
	vector<Plant*> plants;
	string seller;

public:
	Receipt();
	void setSeller( string seller);
	void addPlant(Plant* P);
	void setTotalPrice(double price);
	string toString();  // New method to get receipt as string so it can returned to customer 
	void print();
};

#endif
