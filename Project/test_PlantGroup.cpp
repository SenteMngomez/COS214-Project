/**
 * @file test_PlantGroup.cpp
 * @brief Unit tests for Composite pattern (PlantGroup)
 */

#include <gtest/gtest.h>
#include "PlantGroup.h"
#include "Rose.h"
#include "Tulip.h"
#include "Mango.h"
#include "Begonia.h"
#include "HeavyCareStrategy.h"
#include "ModerateCareStrategy.h"
#include "LightCareStrategy.h"

class PlantGroupTest : public ::testing::Test {
protected:
    PlantGroup* group;
    Plant* rose;
    Plant* tulip;
    Plant* mango;
    Plant* begonia;
    HeavyCareStrategy* heavyCare;
    ModerateCareStrategy* moderateCare;
    LightCareStrategy* lightCare;

    void SetUp() override {
        heavyCare = new HeavyCareStrategy();
        moderateCare = new ModerateCareStrategy();
        lightCare = new LightCareStrategy();
        
        group = new PlantGroup("Test Group", heavyCare, 0.0);
        rose = new Rose("Red", heavyCare, 15.99);
        tulip = new Tulip("Yellow", heavyCare, 12.49);
        mango = new Mango("Green", moderateCare, 25.99);
        begonia = new Begonia("Pink", lightCare, 10.99);
    }

    void TearDown() override {
        delete group;
        delete rose;
        delete tulip;
        delete mango;
        delete begonia;
        delete heavyCare;
        delete moderateCare;
        delete lightCare;
    }
};

// Test adding and getting children
TEST_F(PlantGroupTest, AddAndRemoveChild) {
    group->add(*rose);
    group->add(*tulip);
    group->add(*mango);
    group->add(*begonia);

    // Test that we can find children by tag
    rose->setTag("1");
    tulip->setTag("2");
    mango->setTag("3");
    begonia->setTag("4");
    
    EXPECT_EQ(group->getChild("1"), rose);
    EXPECT_EQ(group->getChild("2"), tulip);
    EXPECT_EQ(group->getChild("3"), mango);
    EXPECT_EQ(group->getChild("4"), begonia);
    EXPECT_EQ(group->getChild("5"), nullptr);  // Non-existent tag
}

// Test removing children
TEST_F(PlantGroupTest, RemoveChild) {
    rose->setTag("1");
    tulip->setTag("2");
    group->add(*rose);
    group->add(*tulip);
    group->remove(*rose);  // Remove rose

    EXPECT_EQ(group->getChild("2"), tulip);  // Tulip should be the only child left
    EXPECT_EQ(group->getChild("1"), nullptr);
}

// Test getType for group
TEST_F(PlantGroupTest, GetType) {
    EXPECT_EQ(group->getType(), "PlantGroup");  // Empty group

    group->add(*rose);
    group->add(*tulip);
    group->add(*mango);
    group->add(*begonia);
    EXPECT_EQ(group->getType(), "Rose, Tulip, Mango, Begonia");
}

// Test print (capture output)
TEST_F(PlantGroupTest, Print) {
    group->add(*rose);

    testing::internal::CaptureStdout();
    group->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("PlantGroup"), std::string::npos);
    EXPECT_NE(output.find("Rose"), std::string::npos);
}

// Test cloning PlantGroup
TEST_F(PlantGroupTest, Clone) {
    rose->setTag("1");
    tulip->setTag("2");
    mango->setTag("3");
    begonia->setTag("4");
    group->add(*rose);
    group->add(*tulip);
    group->add(*mango);
    group->add(*begonia);

    Plant* clonedGroup = group->clone();
    ASSERT_NE(clonedGroup, nullptr);
    EXPECT_EQ(clonedGroup->getType(), "Rose, Tulip, Mango, Begonia");

    // Check if children are cloned (not the same pointers)
    Plant* child1 = dynamic_cast<PlantGroup*>(clonedGroup)->getChild("1");
    Plant* child2 = dynamic_cast<PlantGroup*>(clonedGroup)->getChild("2");
    Plant* child3 = dynamic_cast<PlantGroup*>(clonedGroup)->getChild("3");
    Plant* child4 = dynamic_cast<PlantGroup*>(clonedGroup)->getChild("4");
    ASSERT_NE(child1, nullptr);
    ASSERT_NE(child2, nullptr);
    ASSERT_NE(child3, nullptr);
    ASSERT_NE(child4, nullptr);
    EXPECT_EQ(child1->getType(), "Rose");
    EXPECT_EQ(child2->getType(), "Tulip");
    EXPECT_EQ(child3->getType(), "Mango");
    EXPECT_EQ(child4->getType(), "Begonia");
    EXPECT_EQ(child1->getTag(), "1");
    EXPECT_EQ(child2->getTag(), "2");
    EXPECT_EQ(child3->getTag(), "3");
    EXPECT_EQ(child4->getTag(), "4");

    delete clonedGroup;
}

// Test empty group operations
TEST_F(PlantGroupTest, EmptyGroupOperations) {
    EXPECT_EQ(group->getChild("0"), nullptr);
    EXPECT_EQ(group->getType(), "PlantGroup");

    // Removing from empty group should not crash
    EXPECT_NO_THROW(group->remove(*rose));
}