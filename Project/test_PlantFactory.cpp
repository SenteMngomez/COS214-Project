/**
 * @file test_PlantFactory.cpp
 * @brief Unit tests for Factory pattern (FlowerFactory, TreeFactory, SucculentFactory)
 */

#include <gtest/gtest.h>
#include "FlowerFactory.h"
#include "TreeFactory.h"
#include "SucculentFactory.h"
#include "Rose.h"
#include "Tulip.h"
#include "Mango.h"
#include "Oak.h"
#include "Begonia.h"
#include "Cactus.h"

class PlantFactoryTest : public ::testing::Test {
protected:
    FlowerFactory flowerFactory;
    TreeFactory treeFactory;
    SucculentFactory succulentFactory;

    void SetUp() override {
        // Set up code before each test
    }

    void TearDown() override {
        // Clean up code after each test
    }
};

// Test FlowerFactory
TEST_F(PlantFactoryTest, FlowerFactoryCreatesRose) {
    Plant* plant = flowerFactory.createPlant("Rose", "Red");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->getType(), "Rose");
    EXPECT_EQ(plant->getColour(), "Red");
    EXPECT_DOUBLE_EQ(plant->getPrice(), 15.99);
    delete plant;
}

TEST_F(PlantFactoryTest, FlowerFactoryCreatesTulip) {
    Plant* plant = flowerFactory.createPlant("Tulip", "Yellow");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->getType(), "Tulip");
    EXPECT_EQ(plant->getColour(), "Yellow");
    EXPECT_DOUBLE_EQ(plant->getPrice(), 12.49);
    delete plant;
}

TEST_F(PlantFactoryTest, FlowerFactoryInvalidType) {
    Plant* plant = flowerFactory.createPlant("Invalid", "Blue");
    EXPECT_EQ(plant, nullptr);
}

// Test TreeFactory
TEST_F(PlantFactoryTest, TreeFactoryCreatesMango) {
    Plant* plant = treeFactory.createPlant("Mango", "Green");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->getType(), "Mango");
    EXPECT_EQ(plant->getColour(), "Green");
    EXPECT_DOUBLE_EQ(plant->getPrice(), 25.99);
    delete plant;
}

TEST_F(PlantFactoryTest, TreeFactoryCreatesOak) {
    Plant* plant = treeFactory.createPlant("Oak", "Brown");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->getType(), "Oak");
    EXPECT_EQ(plant->getColour(), "Brown");
    EXPECT_DOUBLE_EQ(plant->getPrice(), 30.99);
    delete plant;
}

TEST_F(PlantFactoryTest, TreeFactoryInvalidType) {
    Plant* plant = treeFactory.createPlant("Invalid", "Purple");
    EXPECT_EQ(plant, nullptr);
}

// Test SucculentFactory
TEST_F(PlantFactoryTest, SucculentFactoryCreatesBegonia) {
    Plant* plant = succulentFactory.createPlant("Begonia", "Pink");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->getType(), "Begonia");
    EXPECT_EQ(plant->getColour(), "Pink");
    EXPECT_DOUBLE_EQ(plant->getPrice(), 10.99);
    delete plant;
}

TEST_F(PlantFactoryTest, SucculentFactoryCreatesCactus) {
    Plant* plant = succulentFactory.createPlant("Cactus", "Green");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->getType(), "Cactus");
    EXPECT_EQ(plant->getColour(), "Green");
    EXPECT_DOUBLE_EQ(plant->getPrice(), 8.99);
    delete plant;
}

TEST_F(PlantFactoryTest, SucculentFactoryInvalidType) {
    Plant* plant = succulentFactory.createPlant("Invalid", "Orange");
    EXPECT_EQ(plant, nullptr);
}

// Test factory with different colors
TEST_F(PlantFactoryTest, FlowerFactoryCustomColor) {
    Plant* plant = flowerFactory.createPlant("Rose", "Blue");
    ASSERT_NE(plant, nullptr);
    EXPECT_EQ(plant->getType(), "Rose");
    EXPECT_EQ(plant->getColour(), "Blue");
    delete plant;
}