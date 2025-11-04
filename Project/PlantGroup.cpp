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
        Plant* clonedChild = child->clone();
        clonedGroup->children.push_back(clonedChild);  // Direct ownership
        clonedGroup->types.push_back(clonedChild->getType());
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
        // Calculate the index to remove the corresponding type
        size_t index = it - children.begin();
        children.erase(it);
        
        // Also remove the corresponding type to keep vectors synchronized
        if(index < types.size()) {
            types.erase(types.begin() + index);
        }
        
        // Note: PlantGroup originally owned the plant, so we should delete it
        // This maintains consistency with the destructor behavior
        delete &plant;
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
    // Delete all child plants
    for(Plant* child : children) {
        delete child;
    }
    children.clear();
}
