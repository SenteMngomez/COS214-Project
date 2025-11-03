#include "GIveSunlight.h"

GiveSunlight::GiveSunlight():Command(){}

void GiveSunlight::execute(vector<string> *tag, string decorator)
{
    if(tag == NULL){
        return ;
    }

    if(tag->empty()){
        return ;
    }
    for(string id :*tag){
        if(greenHouse){
            greenHouse->giveSunlight(id);
            cout<<"The plant with the following id is being left in the sun for some time : "<<id<<endl;
        }
    }
}
