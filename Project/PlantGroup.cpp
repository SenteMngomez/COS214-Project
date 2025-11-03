/**
 * @file PlantGroup.cpp
 * @brief Implementation of PlantGroup class
 * @author Brayden
 * @date October 26, 2025
 */

#include "PlantGroup.h"
#include <iostream>
#include <algorithm>

PlantGroup::PlantGroup(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {}

string PlantGroup::getType() const{
    if(types.empty()) return "PlantGroup";
    string result;
    for(size_t i = 0; i < types.size(); ++i){
        if(i > 0) result += ", ";
        result += types[i];
    }
    return result;
}

Plant* PlantGroup::clone(){
    PlantGroup* clonedGroup = new PlantGroup(getColour(), nullptr, getPrice());
    for(Plant* child : children){
        clonedGroup->add(*child->clone());
    }
    return clonedGroup;
}

void PlantGroup::print(){
    cout << "PlantGroup (" << getType() << "), Price: R" << getPrice() << endl;
    cout << "Children:" << endl;
    for(size_t i = 0; i < children.size(); ++i){
        cout << "  [" << i << "] ";
        children[i]->print();
    }
}

void PlantGroup::add(Plant& plant){
    children.push_back(&plant);
    types.push_back(plant.getType());
}

void PlantGroup::remove(Plant& plant){
    auto it = find(children.begin(), children.end(), &plant);
    if(it != children.end()){
        children.erase(it);
    }
}

Plant* PlantGroup::getChild(string tag){
    for(Plant* child : children){
        if(child && child->getTag() == tag){
            return child;
        }
    }
    return nullptr;
}

PlantGroup::~PlantGroup() {
    
}
