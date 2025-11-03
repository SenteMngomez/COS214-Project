#include <gtest/gtest.h>
#include "SeedState.h"
#include "SproutState.h"
#include "MatureState.h"
#include "DeadState.h"
#include "Plant.h"
#include <string>
#include <iostream>
using namespace std;

class MockPlant : public Plant{
    public:
        MockPlant():Plant("green",nullptr,50.0){}
        virtual ~MockPlant(){}
        string getType() const override {return "MockPlant";}
        Plant* clone() override {return new MockPlant(*this);}
        void print() override{}
        void add(Plant& plant)override{}
        void remove(Plant& plant) override{}
        Plant* getChild(string) override {return nullptr;}
};

// ********************************SEED STATE TEST*****************************************
TEST(PlantStateTest, SeedStateHandlesCorrectly){
    MockPlant plant;
    SeedState seed;

    plant.setState(new SeedState());

    testing::internal::CaptureStdout();
    plant.getState()->handle(&plant);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Germinating from seed to sprout. Critical phase!"), string::npos);
    EXPECT_NE(output.find("MockPlant plant received water."), string::npos);
    EXPECT_NE(output.find("MockPlant plant received sunlight."), string::npos);
    EXPECT_NE(output.find("Seed has successfully germinated into a MockPlant sprout!"), string::npos);

    EXPECT_NE(dynamic_cast<SproutState*>(plant.getState()), nullptr);
}

// ********************************SPROUT STATE TEST*****************************************
TEST(PlantStateTest, SproutStateHandlesCorrectly){
    MockPlant plant;
    SproutState seed;

    plant.setState(new SproutState());

    testing::internal::CaptureStdout();
    plant.getState()->handle(&plant);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("The MockPlant sprout is growing and needs care."), string::npos);
    EXPECT_NE(output.find("MockPlant plant received water."), string::npos);
    EXPECT_NE(output.find("MockPlant plant received sunlight."), string::npos);
    EXPECT_NE(output.find("The sprout has finally matured into a full MockPlant. #grown"), string::npos);

    EXPECT_NE(dynamic_cast<MatureState*>(plant.getState()), nullptr);
}


// ********************************MATURE STATE TEST*****************************************
TEST(PlantStateTest, MatureStateHandlesCorrectly){
    MockPlant plant;
    MatureState seed;

    plant.setState(new MatureState());

    testing::internal::CaptureStdout();
    plant.getState()->handle(&plant);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("The MockPlant needs normal care."), string::npos);
    EXPECT_NE(output.find("MockPlant plant received water"), string::npos);
    EXPECT_NE(output.find("MockPlant plant received sunlight."), string::npos);
    EXPECT_NE(output.find("The MockPlant is aging and may soon die."), string::npos);

    EXPECT_NE(dynamic_cast<DeadState*>(plant.getState()), nullptr);
}


// ********************************DEAD STATE TEST*****************************************
TEST(PlantStateTest, DeadStateHandlesCorrectly){
    MockPlant plant;
    DeadState seed;

    plant.setState(new DeadState());

    testing::internal::CaptureStdout();
    plant.getState()->handle(&plant);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("The MockPlant is dead and can no longer grow. RIP"), string::npos);

    EXPECT_NE(dynamic_cast<DeadState*>(plant.getState()), nullptr);
}