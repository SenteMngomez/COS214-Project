#include <gtest/gtest.h>
#include "Greenhouse.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"
#include "TreeFactory.h"

class GreenhouseTest : public ::testing::Test {
    protected:
        Greenhouse greenhouse{"Test Greenhouse"};
        FlowerFactory flowerFactory;
        SucculentFactory succulentFactory;
        TreeFactory treeFactory;

        void SetUp() override {
            //Set up code before each test
        }

        void TearDown() override {
            //Clean up code after each test
        }

};

TEST_F(GreenhouseTest, AddPlant){

    Plant* rose = flowerFactory.createPlant("Rose");

    ASSERT_NE(rose, nullptr);
    greenhouse.addPlant(rose);

    //Verify by checking iterator or showPlants
    Iterator* iter = greenhouse.createIterator();
    ASSERT_NE(iter, nullptr);
    delete iter;

}

TEST_F(GreenhouseTest, AddMultiplePlants) {

    Plant* rose = flowerFactory.createPlant("Rose");
    Plant* cactus = succulentFactory.createPlant("Cactus");
    Plant* oak = treeFactory.createPlant("Oak");

    greenhouse.addPlant(rose);
    greenhouse.addPlant(cactus);
    greenhouse.addPlant(oak);

    EXPECT_NE(rose, nullptr);
    EXPECT_NE(cactus, nullptr);
    EXPECT_NE(oak, nullptr);

}

TEST_F(GreenhouseTest, RemovePlant) {

    Plant* rose = flowerFactory.createPlant("Rose");
    greenhouse.addPlant(rose);

    int tag = rose->getTag();
    Plant* removed = greenhouse.removePlant(tag);

    ASSERT_NE(removed, nullptr);
    EXPECT_EQ(removed->getTag(), tag);

}

TEST_F(GreenhouseTest, RemoveNonExistentPlant) {

    Plant* removed = greenhouse.removePlant(9999);
    EXPECT_EQ(removed, nullptr);

}

TEST_F(GreenhouseTest, WaterPlant) {

    Plant* rose = flowerFactory.createPlant("Rose");
    greenhouse.addPlant(rose);
    int tag = rose->getTag();
    EXPECT_NO_THROW(greenhouse.waterPlant(tag));

}

TEST_F(GreenhouseTest, WaterNonEXistentPlant) {
    EXPECT_NO_THROW(greenhouse.waterPlant(9999));
}

TEST_F(GreenhouseTest, GiveSunlight) {

    Plant* rose = flowerFactory.createPlant("Rose");
    greenhouse.addPlant(rose);
    int tag = rose->getTag();
    EXPECT_NO_THROW(greenhouse.giveSunlight(tag));

}

TEST_F(GreenhouseTest, GiveSunlightNonEXistentPlant) {
    EXPECT_NO_THROW(greenhouse.giveSunlight(9999));
}

TEST_F(GreenhouseTest, GetName) {
    EXPECT_EQ(greenhouse.getName(), "Test Greenhouse");
}

TEST_F(GreenhouseTest, CreateIterator) {

    Plant* rose = flowerFactory.createPlant("Rose");
    greenhouse.addPlant(rose);

    Iterator* iter = greenhouse.createIterator();
    ASSERT_NE(iter, nullptr);
    delete iter;

}

TEST_F(GreenhouseTest, ShowPlants) {

    Plant* rose = flowerFactory.createPlant("Rose");
    greenhouse.addPlant(rose);

    EXPECT_NO_THROW(greenhouse.showPlants());

}

TEST_F(GreenhouseTest, ShowPlantsEmpty) {
    EXPECT_NO_THROW(greenhouse.showPlants());
}

int main(int argc, char** argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}