/**
 * @file test_Plant.cpp
 * @brief Unit tests for Plant class (including embedded Prototype)
 */

#include <gtest/gtest.h>
#include "Rose.h"
#include "Tulip.h"
#include "Mango.h"
#include "Oak.h"
#include "Begonia.h"
#include "Cactus.h"
#include "SeedState.h"
#include "HeavyCareStrategy.h"
#include "ModerateCareStrategy.h"
#include "LightCareStrategy.h"

class PlantTest : public ::testing::Test{
protected:
    // Flower plants (HeavyCareStrategy)
    Plant* rose;
    Plant* tulip;
    HeavyCareStrategy* heavyCare;

    // Tree plants (ModerateCareStrategy)
    Plant* mango;
    Plant* oak;
    ModerateCareStrategy* moderateCare;

    // Succulent plants (LightCareStrategy)
    Plant* begonia;
    Plant* cactus;
    LightCareStrategy* lightCare;

    void SetUp() override{
        heavyCare = new HeavyCareStrategy();
        moderateCare = new ModerateCareStrategy();
        lightCare = new LightCareStrategy();

        rose = new Rose("Red", heavyCare, 15.99);
        tulip = new Tulip("Yellow", heavyCare, 12.49);
        mango = new Mango("Green", moderateCare, 25.99);
        oak = new Oak("Brown", moderateCare, 30.99);
        begonia = new Begonia("Pink", lightCare, 10.99);
        cactus = new Cactus("Green", lightCare, 8.99);
    }

    void TearDown() override {
        delete rose;
        delete tulip;
        delete mango;
        delete oak;
        delete begonia;
        delete cactus;
        delete heavyCare;
        delete moderateCare;
        delete lightCare;
    }
};

// Test basic Plant properties (colour, price, tag, type)
TEST_F(PlantTest, BasicProperties) {
    EXPECT_EQ(rose->getColour(), "Red");
    EXPECT_DOUBLE_EQ(rose->getPrice(), 15.99);
    EXPECT_EQ(rose->getType(), "Rose");

    // Test tag setting/getting
    rose->setTag("42");
    EXPECT_EQ(rose->getTag(), "42");
}

// Test state management
TEST_F(PlantTest, StateManagement) {
    PlantState* initialState = rose->getState();
    ASSERT_NE(initialState, nullptr);

    // Set a new state (e.g., SeedState)
    PlantState* newState = new SeedState();
    rose->setState(newState);
    EXPECT_EQ(rose->getState(), newState);
}

// Test care operations (delegate to CareStrategy)
TEST_F(PlantTest, CareOperations) {
    EXPECT_NO_THROW(rose->receiveWater());
    EXPECT_NO_THROW(rose->receiveSunlight());
}

// Test care strategy retrieval
TEST_F(PlantTest, CareStrategy) {
    EXPECT_EQ(rose->getCareStrategy(), heavyCare);
    EXPECT_EQ(mango->getCareStrategy(), moderateCare);
    EXPECT_EQ(begonia->getCareStrategy(), lightCare);
}

// Test Prototype (clone)
TEST_F(PlantTest, Clone) {
    rose->setTag("1");

    Plant* clone = rose->clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->getType(), rose->getType());
    EXPECT_EQ(clone->getColour(), rose->getColour());
    EXPECT_DOUBLE_EQ(clone->getPrice(), rose->getPrice());
    EXPECT_EQ(clone->getTag(), rose->getTag());

    delete clone;
}

// Test print (basic no-crash check)
TEST_F(PlantTest, Print) {
    EXPECT_NO_THROW(rose->print());
}

// Test Tulip properties
TEST_F(PlantTest, TulipProperties) {
    EXPECT_EQ(tulip->getColour(), "Yellow");
    EXPECT_DOUBLE_EQ(tulip->getPrice(), 12.49);
    EXPECT_EQ(tulip->getType(), "Tulip");
}

// Test Tulip clone
TEST_F(PlantTest, TulipClone) {
    tulip->setTag("2");

    Plant* clone = tulip->clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->getType(), "Tulip");
    EXPECT_EQ(clone->getColour(), "Yellow");

    delete clone;
}

// Test Mango properties (Tree)
TEST_F(PlantTest, MangoProperties) {
    EXPECT_EQ(mango->getColour(), "Green");
    EXPECT_DOUBLE_EQ(mango->getPrice(), 25.99);
    EXPECT_EQ(mango->getType(), "Mango");
}

// Test Mango clone
TEST_F(PlantTest, MangoClone) {
    mango->setTag("3");

    Plant* clone = mango->clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->getType(), "Mango");
    EXPECT_EQ(clone->getColour(), "Green");

    delete clone;
}

// Test Oak properties (Tree)
TEST_F(PlantTest, OakProperties) {
    EXPECT_EQ(oak->getColour(), "Brown");
    EXPECT_DOUBLE_EQ(oak->getPrice(), 30.99);
    EXPECT_EQ(oak->getType(), "Oak");
}

// Test Oak clone
TEST_F(PlantTest, OakClone) {
    oak->setTag("4");

    Plant* clone = oak->clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->getType(), "Oak");
    EXPECT_EQ(clone->getColour(), "Brown");

    delete clone;
}

// Test Begonia properties (Succulent)
TEST_F(PlantTest, BegoniaProperties) {
    EXPECT_EQ(begonia->getColour(), "Pink");
    EXPECT_DOUBLE_EQ(begonia->getPrice(), 10.99);
    EXPECT_EQ(begonia->getType(), "Begonia");
}

// Test Begonia clone
TEST_F(PlantTest, BegoniaClone) {
    begonia->setTag("5");

    Plant* clone = begonia->clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->getType(), "Begonia");
    EXPECT_EQ(clone->getColour(), "Pink");

    delete clone;
}

// Test Cactus properties (Succulent)
TEST_F(PlantTest, CactusProperties) {
    EXPECT_EQ(cactus->getColour(), "Green");
    EXPECT_DOUBLE_EQ(cactus->getPrice(), 8.99);
    EXPECT_EQ(cactus->getType(), "Cactus");
}

// Test Cactus clone
TEST_F(PlantTest, CactusClone) {
    cactus->setTag("6");

    Plant* clone = cactus->clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->getType(), "Cactus");
    EXPECT_EQ(clone->getColour(), "Green");

    delete clone;
}