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

	void print();
};

#endif
