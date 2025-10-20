#ifndef RECEIPT_H
#define RECEIPT_H

#include <string>
using namespace std;

class Receipt {

private:
	double totalPrice;
	string plantDetails;
	int seller;

public:
	Receipt();

	void print();
};

#endif
