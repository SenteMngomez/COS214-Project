#include "SellPlant.h"

void SellPlant::execute(vector<int>* tag, string decorator) {
	// TODO - implement SellPlant::execute
	if(!tag){
		return ;
	}
	for(int i :*tag){
		if(inventory){
			greenHouse->removePlant(i);//updating greenhouse and auto updates inventory 
			cout<< "Plant greenhouse : "<<this->greenHouse->getName()<<"is selling the following plant id"<<i;
		}
	}
	
}
