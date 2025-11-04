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
    // We'll create plants as needed in each test since PlantGroup takes ownership
    HeavyCareStrategy* heavyCare;
    ModerateCareStrategy* moderateCare;
    LightCareStrategy* lightCare;

    void SetUp() override {
        heavyCare = new HeavyCareStrategy();
        moderateCare = new ModerateCareStrategy();
        lightCare = new LightCareStrategy();
        
        group = new PlantGroup("Test Group", new HeavyCareStrategy(), 0.0);
    }

    void TearDown() override {
        // PlantGroup destructor will handle children automatically
        delete group;
        
        // Clean up strategy objects
        delete heavyCare;
        delete moderateCare;
        delete lightCare;
    }
};

// Test adding and getting children
TEST_F(PlantGroupTest, AddAndRemoveChild) {
    // Create plants that PlantGroup will take ownership of
    Plant* rose = new Rose("Red", new HeavyCareStrategy(), 15.99);
    Plant* tulip = new Tulip("Yellow", new HeavyCareStrategy(), 12.49);
    Plant* mango = new Mango("Green", new ModerateCareStrategy(), 25.99);
    Plant* begonia = new Begonia("Pink", new LightCareStrategy(), 10.99);
    
    rose->setTag("1");
    tulip->setTag("2");
    mango->setTag("3");
    begonia->setTag("4");
    
    group->add(*rose);
    group->add(*tulip);
    group->add(*mango);
    group->add(*begonia);

    // Test that we can find children by tag
    EXPECT_EQ(group->getChild("1"), rose);
    EXPECT_EQ(group->getChild("2"), tulip);
    EXPECT_EQ(group->getChild("3"), mango);
    EXPECT_EQ(group->getChild("4"), begonia);
    EXPECT_EQ(group->getChild("5"), nullptr);  // Non-existent tag
    
    // PlantGroup destructor will clean up the plants
}

// Test removing children
TEST_F(PlantGroupTest, RemoveChild) {
    Plant* rose = new Rose("Red", new HeavyCareStrategy(), 15.99);
    Plant* tulip = new Tulip("Yellow", new HeavyCareStrategy(), 12.49);
    
    rose->setTag("1");
    tulip->setTag("2");
    
    group->add(*rose);
    group->add(*tulip);
    group->remove(*rose);  // Remove rose - PlantGroup will delete it

    EXPECT_EQ(group->getChild("2"), tulip);  // Tulip should be the only child left
    EXPECT_EQ(group->getChild("1"), nullptr);
    
    // Note: rose is now deleted by PlantGroup, no need to manually delete
}

// Test getType for group
TEST_F(PlantGroupTest, GetType) {
    EXPECT_EQ(group->getType(), "PlantGroup");  // Empty group

    Plant* rose = new Rose("Red", new HeavyCareStrategy(), 15.99);
    Plant* tulip = new Tulip("Yellow", new HeavyCareStrategy(), 12.49);
    Plant* mango = new Mango("Green", new ModerateCareStrategy(), 25.99);
    Plant* begonia = new Begonia("Pink", new LightCareStrategy(), 10.99);
    
    group->add(*rose);
    group->add(*tulip);
    group->add(*mango);
    group->add(*begonia);
    EXPECT_EQ(group->getType(), "Rose, Tulip, Mango, Begonia");
}

// Test print (capture output)
TEST_F(PlantGroupTest, Print) {
    Plant* rose = new Rose("Red", new HeavyCareStrategy(), 15.99);
    group->add(*rose);

    testing::internal::CaptureStdout();
    group->print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("PlantGroup"), std::string::npos);
    EXPECT_NE(output.find("Rose"), std::string::npos);
}

// Test cloning PlantGroup
TEST_F(PlantGroupTest, Clone) {
    Plant* rose = new Rose("Red", new HeavyCareStrategy(), 15.99);
    Plant* tulip = new Tulip("Yellow", new HeavyCareStrategy(), 12.49);
    Plant* mango = new Mango("Green", new ModerateCareStrategy(), 25.99);
    Plant* begonia = new Begonia("Pink", new LightCareStrategy(), 10.99);
    
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
    Plant* rose = new Rose("Red", new HeavyCareStrategy(), 15.99);
    EXPECT_NO_THROW(group->remove(*rose));
    delete rose; // Clean up since it wasn't added to group
}