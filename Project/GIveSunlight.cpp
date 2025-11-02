#include "GIveSunlight.h"

GiveSunlight::GiveSunlight():Command(){}

void GiveSunlight::execute(vector<string> *tag, string decorator)
{

    //find a way to use the decorator ??
    for(string id :*tag){
        greenHouse->giveSunlight(id);
        cout<<"The plant with the following id is being left in the sun for some time : "<<id<<endl;

    }
}
