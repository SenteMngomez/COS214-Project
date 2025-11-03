#include <gtest/gtest.h>
#include "ModerateCareStrategy.h"
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

TEST(ModerateCareStrategyIntegrationTest, WaterOutputIsCorrect){
    ModerateCareStrategy strategy;
    MockPlant plant;
    testing::internal::CaptureStdout();

    strategy.water(&plant);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Giving the MockPlant 200-250ml of water."), string::npos);
}

TEST(ModerateCareStrategyIntegrationTest, SunlightOutputIsCorrect){
    ModerateCareStrategy strategy;
    MockPlant plant;
    testing::internal::CaptureStdout();
    strategy.sunlight(&plant);

    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Placing the MockPlant in indirect sunlight for 4-6 hours."), string::npos);
}