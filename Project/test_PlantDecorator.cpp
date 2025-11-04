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
        // Create separate care strategies for each plant to avoid sharing
        rose = new Rose("Red", new HeavyCareStrategy(), 15.99);
        mango = new Mango("Green", new ModerateCareStrategy(), 25.99);
        begonia = new Begonia("Pink", new LightCareStrategy(), 10.99);
        
        // Keep references for other uses, but plants own their strategies
        heavyCare = new HeavyCareStrategy();
        moderateCare = new ModerateCareStrategy();
        lightCare = new LightCareStrategy();
    }

    void TearDown() override {
        // Plants own their care strategies, so only delete what's not transferred
        if (rose) delete rose;
        if (mango) delete mango;
        if (begonia) delete begonia;
        
        // Delete the reference care strategies (these are not used by plants)
        if (heavyCare) delete heavyCare;
        if (moderateCare) delete moderateCare;
        if (lightCare) delete lightCare;
    }
};

// Test DecorativePot
TEST_F(PlantDecoratorTest, DecorativePotWrapsPlant) {
    Plant* decorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());
    rose = nullptr; // Ownership transferred to decorator

    EXPECT_EQ(decorated->getType(), "Rose in Ceramic");
    EXPECT_EQ(decorated->getColour(), "Red");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 15.99);

    delete decorated;
}

TEST_F(PlantDecoratorTest, DecorativePotPrint) {
    Plant* decorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());
    rose = nullptr; // Ownership transferred to decorator

    testing::internal::CaptureStdout();
    decorated->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Ceramic pot"), std::string::npos);

    delete decorated;
}

// Test GiftWrapDecorator
TEST_F(PlantDecoratorTest, GiftWrapDecoratorWrapsPlant) {
    Plant* decorated = new GiftWrapDecorator(rose, "Ribbon", rose->getColour(), nullptr, rose->getPrice());
    rose = nullptr; // Ownership transferred to decorator

    EXPECT_EQ(decorated->getType(), "Rose with Ribbon");
    EXPECT_EQ(decorated->getColour(), "Red");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 15.99);

    delete decorated;
}

TEST_F(PlantDecoratorTest, GiftWrapDecoratorPrint) {
    Plant* decorated = new GiftWrapDecorator(rose, "Ribbon", rose->getColour(), nullptr, rose->getPrice());
    rose = nullptr; // Ownership transferred to decorator

    testing::internal::CaptureStdout();
    decorated->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Wrapped with Ribbon"), std::string::npos);

    delete decorated;
}

// Test chaining decorators
TEST_F(PlantDecoratorTest, ChainedDecorators) {
    Plant* potDecorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());
    rose = nullptr; // Ownership transferred to first decorator
    Plant* fullyDecorated = new GiftWrapDecorator(potDecorated, "Ribbon", potDecorated->getColour(), nullptr, potDecorated->getPrice());

    EXPECT_EQ(fullyDecorated->getType(), "Rose in Ceramic with Ribbon");

    delete fullyDecorated;
}

// Test cloning decorated plants
TEST_F(PlantDecoratorTest, DecorativePotClone) {
    Plant* decorated = new DecorativePot(rose, "Ceramic", rose->getColour(), nullptr, rose->getPrice());
    rose = nullptr; // Ownership transferred to decorator
    Plant* cloned = decorated->clone();

    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->getType(), decorated->getType());
    EXPECT_EQ(cloned->getColour(), decorated->getColour());

    delete decorated;
    delete cloned;
}

TEST_F(PlantDecoratorTest, GiftWrapDecoratorClone) {
    Plant* decorated = new GiftWrapDecorator(rose, "Ribbon", rose->getColour(), nullptr, rose->getPrice());
    rose = nullptr; // Ownership transferred to decorator
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
    mango = nullptr; // Ownership transferred to decorator

    EXPECT_EQ(decorated->getType(), "Mango in Clay");
    EXPECT_EQ(decorated->getColour(), "Green");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 25.99);

    delete decorated;
}

TEST_F(PlantDecoratorTest, GiftWrapDecoratorWithBegonia) {
    Plant* decorated = new GiftWrapDecorator(begonia, "Paper", begonia->getColour(), nullptr, begonia->getPrice());
    begonia = nullptr; // Ownership transferred to decorator

    EXPECT_EQ(decorated->getType(), "Begonia with Paper");
    EXPECT_EQ(decorated->getColour(), "Pink");
    EXPECT_DOUBLE_EQ(decorated->getPrice(), 10.99);

    delete decorated;
}

// Test chaining decorators with different plant types
TEST_F(PlantDecoratorTest, ChainedDecoratorsWithMango) {
    Plant* potDecorated = new DecorativePot(mango, "Wooden", mango->getColour(), nullptr, mango->getPrice());
    mango = nullptr; // Ownership transferred to first decorator
    Plant* fullyDecorated = new GiftWrapDecorator(potDecorated, "Gold Ribbon", potDecorated->getColour(), nullptr, potDecorated->getPrice());

    EXPECT_EQ(fullyDecorated->getType(), "Mango in Wooden with Gold Ribbon");

    delete fullyDecorated;
}