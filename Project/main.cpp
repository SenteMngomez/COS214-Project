#include <iostream>
#include <string>
#include "Plant.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"
#include "TreeFactory.h"
#include "SeedState.h"
#include "Greenhouse.h"
#include "GreenhouseInterface.h"

using namespace std;



int main() {

    Greenhouse greenhouse("Green Home");

    FlowerFactory flowerFactory;
    SucculentFactory succulentFactory;
    TreeFactory treeFactory;

    Plant* rose = flowerFactory.createPlant("Rose");
    Plant* cactus = succulentFactory.createPlant("Cactus");
    Plant* oak = treeFactory.createPlant("Oak");

    greenhouse.addPlant(rose);
    greenhouse.addPlant(cactus);
    greenhouse.addPlant(oak);

    greenhouse.showPlants();

    
    
    return 0;

}