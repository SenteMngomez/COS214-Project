/**
 * @file FlowerFactory.cpp
 * @brief Implementation of FlowerFactory
 * @author Brayden
 * @date October 26, 2025
 */

#include "FlowerFactory.h"

Plant* FlowerFactory::createPlant(string type, string colour){
	if(type == "Rose"){
		colour=colour.empty()?"Red":colour;
        setProduct(new Rose(colour, new HeavyCareStrategy(), 15.99));
        return getProduct();
    }else if(type == "Tulip"){
		colour=colour.empty()?"Yellow":colour;
        setProduct(new Tulip(colour, new HeavyCareStrategy(), 12.49));
        return getProduct();
    }
    return nullptr;
}
