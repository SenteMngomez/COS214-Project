/**
 * @file TreeFactory.cpp
 * @brief Implementation of TreeFactory
 * @author Brayden
 * @date October 26, 2025
 */

#include "TreeFactory.h"
#include "Mango.h"
#include "Oak.h"

Plant* TreeFactory::createPlant(string type) {
    if(type == "Mango"){
        setProduct(new Mango("Green", nullptr, 25.99));
        return getProduct();
    }else if(type == "Oak") {
        setProduct(new Oak("Brown", nullptr, 30.99));
        return getProduct();
    }
    return nullptr;
}
