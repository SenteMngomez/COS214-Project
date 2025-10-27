#include "WaterPlant.h"

WaterPlant::WaterPlant():Command(){}


void WaterPlant::execute(vector<int> *tag, string decorator)
{
    for(int id : *tag){
        greenHouse->waterPlant(id);
        cout<<"Plants with the following id has been watered: "<<id<<endl;
    }

}
