#include "WaterPlant.h"

WaterPlant::WaterPlant():Command(){}


void WaterPlant::execute(vector<string> *tag, string decorator)
{
    for(string id : *tag){
        greenHouse->waterPlant(id);
        cout<<"Plants with the following id has been watered: "<<id<<endl;
    }

}
