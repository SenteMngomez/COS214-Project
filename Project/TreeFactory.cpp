/**
 * @file TreeFactory.cpp
 * @brief Implementation of TreeFactory
 * @author Brayden
 * @date October 26, 2025
 */

#include "TreeFactory.h"
#include "Mango.h"
#include "Oak.h"

Plant* TreeFactory::createPlant(string type, string colour) {
    if(type == "Mango"){
		colour=colour.empty()?"Brown":colour;
        setProduct(new Mango(colour, new ModerateCareStrategy(), 25.99));
        return getProduct();
    }else if(type == "Oak") {
		colour=colour.empty()?"Brown":colour;
        setProduct(new Oak(colour, new ModerateCareStrategy, 30.99));
        return getProduct();
    }
    return nullptr;
}
