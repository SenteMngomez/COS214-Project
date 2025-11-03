/**
 * @file test_PlantDecorator.cpp
 * @brief Unit tests for Decorator pattern (DecorativePot, GiftWrapDecorator)
 */

#include <gtest/gtest.h>
#include "DecorativePot.h"
#include "GiftWrapDecorator.h"
#include "Rose.h"
#include "Mango.h"
#include "Begonia.h"
#include "HeavyCareStrategy.h"
#include "ModerateCareStrategy.h"
#include "LightCareStrategy.h"

class PlantDecoratorTest : public ::testing::Test {
protected:
    Plant* rose;
    Plant* mango;
    Plant* begonia;
    HeavyCareStrategy* heavyCare;
    ModerateCareStrategy* moderateCare;
    LightCareStrategy* lightCare;

    void SetUp() override {
        heavyCare = new HeavyCareStrategy();
        moderateCare = new ModerateCareStrategy();
        lightCare = new LightCareStrategy();
        
        rose = new Rose("Red", heavyCare, 15.99);
        mango = new Mango("Green", moderateCare, 25.99);
        begonia = new Begonia("Pink", lightCare, 10.99);
    }

    void TearDown() override {
        delete rose;
        delete mango;
        delete begonia;
        delete heavyCare;
        delete moderateCare;
        delete lightCare;
    }
};

// Test DecorativePot
TEST_F(PlantDecoratorTest, DecorativePotWrapsPlant) {
    Plant* decorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());

    EXPECT_EQ(decorated->getType(), "Rose in Ceramic");
    EXPECT_EQ(decorated->getColour(), "Red");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 15.99);

    delete decorated;
}

TEST_F(PlantDecoratorTest, DecorativePotPrint) {
    Plant* decorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());

    testing::internal::CaptureStdout();
    decorated->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Ceramic pot"), std::string::npos);

    delete decorated;
}

// Test GiftWrapDecorator
TEST_F(PlantDecoratorTest, GiftWrapDecoratorWrapsPlant) {
    Plant* decorated = new GiftWrapDecorator(rose, "Ribbon", rose->getColour(), nullptr, rose->getPrice());

    EXPECT_EQ(decorated->getType(), "Rose with Ribbon");
    EXPECT_EQ(decorated->getColour(), "Red");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 15.99);

    delete decorated;
}

TEST_F(PlantDecoratorTest, GiftWrapDecoratorPrint) {
    Plant* decorated = new GiftWrapDecorator(rose, "Ribbon", rose->getColour(), nullptr, rose->getPrice());

    testing::internal::CaptureStdout();
    decorated->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Wrapped with Ribbon"), std::string::npos);

    delete decorated;
}

// Test chaining decorators
TEST_F(PlantDecoratorTest, ChainedDecorators) {
    Plant* potDecorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());
    Plant* fullyDecorated = new GiftWrapDecorator(potDecorated, "Ribbon", potDecorated->getColour(), nullptr, potDecorated->getPrice());

    EXPECT_EQ(fullyDecorated->getType(), "Rose in Ceramic with Ribbon");

    delete fullyDecorated;
}

// Test cloning decorated plants
TEST_F(PlantDecoratorTest, DecorativePotClone) {
    Plant* decorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());
    Plant* cloned = decorated->clone();

    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->getType(), decorated->getType());
    EXPECT_EQ(cloned->getColour(), decorated->getColour());

    delete decorated;
    delete cloned;
}

TEST_F(PlantDecoratorTest, GiftWrapDecoratorClone) {
    Plant* decorated = new GiftWrapDecorator(rose, "Ribbon", rose->getColour(), nullptr, rose->getPrice());
    Plant* cloned = decorated->clone();

    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->getType(), decorated->getType());
    EXPECT_EQ(cloned->getColour(), decorated->getColour());

    delete decorated;
    delete cloned;
}

// Test decorating different plant types
TEST_F(PlantDecoratorTest, DecorativePotWithMango) {
    Plant* decorated = new DecorativePot(mango, "Clay", mango->getColour(), nullptr, mango->getPrice());

    EXPECT_EQ(decorated->getType(), "Mango in Clay");
    EXPECT_EQ(decorated->getColour(), "Green");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 25.99);

    delete decorated;
}

TEST_F(PlantDecoratorTest, GiftWrapDecoratorWithBegonia) {
    Plant* decorated = new GiftWrapDecorator(begonia, "Paper", begonia->getColour(), nullptr, begonia->getPrice());

    EXPECT_EQ(decorated->getType(), "Begonia with Paper");
    EXPECT_EQ(decorated->getColour(), "Pink");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 10.99);

    delete decorated;
}

// Test chaining decorators with different plant types
TEST_F(PlantDecoratorTest, ChainedDecoratorsWithMango) {
    Plant* potDecorated = new DecorativePot(mango, "Wooden", mango->getColour(), nullptr, mango->getPrice());
    Plant* fullyDecorated = new GiftWrapDecorator(potDecorated, "Gold Ribbon", potDecorated->getColour(), nullptr, potDecorated->getPrice());

    EXPECT_EQ(fullyDecorated->getType(), "Mango in Wooden with Gold Ribbon");

    delete fullyDecorated;
}