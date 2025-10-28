/**
 * @file SucculentFactory.cpp
 * @brief Implementation of SucculentFactory
 * @author Brayden
 * @date October 26, 2025
 */

#include "SucculentFactory.h"
#include "Begonia.h"
#include "Cactus.h"

Plant* SucculentFactory::createPlant(string type) {
    if(type == "Begonia"){
        setProduct(new Begonia("Pink", nullptr, 10.99));
        return getProduct();
    }else if(type == "Cactus") {
        setProduct(new Cactus("Green", nullptr, 8.99));
        return getProduct();
    }
    return nullptr;
}
