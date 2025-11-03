#include <gtest/gtest.h>
#include "HeavyCareStrategy.h"
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
        Plant* getChild(int) override {return nullptr;}
};

TEST(HeavyCareStrategyIntegrationTest, WaterOutputIsCorrect){
    HeavyCareStrategy strategy;
    MockPlant plant;
    testing::internal::CaptureStdout();

    strategy.water(&plant);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Giving the MockPlant 300-350ml of water."), string::npos);
}

TEST(HeavyCareStrategyIntegrationTest, SunlightOutputIsCorrect){
    HeavyCareStrategy strategy;
    MockPlant plant;
    testing::internal::CaptureStdout();
    strategy.sunlight(&plant);

    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Placing the MockPlant in direct sunlight for 6-9 hours."), string::npos);
}

int main(int argc,char**argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}