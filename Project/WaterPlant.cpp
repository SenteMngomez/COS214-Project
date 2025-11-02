#include "WaterPlant.h"

WaterPlant::WaterPlant():Command(){}


void WaterPlant::execute(vector<int> *tag, string decorator)
{
    if(tag == NULL) {
        return;
    }

    if(tag->empty()) {
        return;
    }

    for(int id : *tag){
        if(greenHouse){   
            greenHouse->waterPlant(id);
            cout<<"Plants with the following id has been watered: "<<id<<endl;
        }
    }

}
