/**
 * @file SucculentFactory.cpp
 * @brief Implementation of SucculentFactory
 * @author Brayden
 * @date October 26, 2025
 */

#include "SucculentFactory.h"
#include "Begonia.h"
#include "Cactus.h"

Plant* SucculentFactory::createPlant(string type, string colour) {
    if(type == "Begonia"){
		colour=colour.empty()?"Pink":colour;
        setProduct(new Begonia(colour, new LightCareStrategy(), 10.99));
        return getProduct();
    }else if(type == "Cactus") {
		colour=colour.empty()?"Green":colour;
        setProduct(new Cactus(colour, new LightCareStrategy(), 8.99));
        return getProduct();
    }
    return nullptr;
}
