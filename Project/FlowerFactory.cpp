/**
 * @file FlowerFactory.cpp
 * @brief Implementation of FlowerFactory
 * @author Brayden
 * @date October 26, 2025
 */

#include "FlowerFactory.h"

Plant* FlowerFactory::createPlant(string type){
	if(type == "Rose"){
        setProduct(new Rose("Red", nullptr, 15.99));
        return getProduct();
    }else if(type == "Tulip"){
        setProduct(new Tulip("Yellow", nullptr, 12.49));
        return getProduct();
    }
    return nullptr;
}
