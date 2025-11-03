#include <gtest/gtest.h>
#include "LightCareStrategy.h"
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

TEST(LightCareStrategyIntegrationTest, WaterOutputIsCorrect){
    LightCareStrategy strategy;
    MockPlant plant;
    testing::internal::CaptureStdout();

    strategy.water(&plant);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Giving the MockPlant 100ml of water."), string::npos);
}

TEST(LightCareStrategyIntegrationTest, SunlightOutputIsCorrect){
    LightCareStrategy strategy;
    MockPlant plant;
    testing::internal::CaptureStdout();
    strategy.sunlight(&plant);

    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Placing the MockPlant in direct sunlight for 3-4 hours."), string::npos);
}
