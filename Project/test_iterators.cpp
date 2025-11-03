#include <gtest/gtest.h>
#include "Plant.h"
#include "Iterator.h"
#include "PlantIterator.h"
#include "ChatIterator.h"
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

//****************************Plant Iterator Tests****************** 
TEST(PlantIteratorTest, IteratesCorrectly){
    vector<Plant*> plants = {new MockPlant(),new MockPlant(),new MockPlant()};
    PlantIterator it(plants);
    it.first();
    EXPECT_EQ(it.currentItem()->getType(), "MockPlant");
    it.next();
    EXPECT_EQ(it.currentItem()->getType(), "MockPlant");
    it.next();
    EXPECT_EQ(it.currentItem()->getType(), "MockPlant");
    it.next();
    EXPECT_TRUE(it.isDone());
    for (Plant* p : plants) delete p;
}

//****************************Chat Iterator Tests****************** 
TEST(ChatIteratorTest, IteratesCorrectly){
    vector<string> messages = {"Heyyy","Yoh this rose is nice","I'd like to buy this"};
    ChatIterator it(&messages);

    it.first();
    EXPECT_EQ(it.currentItem(),"Heyyy");
    it.next();
    EXPECT_EQ(it.currentItem(),"Yoh this rose is nice");
    it.next();
    EXPECT_EQ(it.currentItem(),"I'd like to buy this");
    it.next();
    EXPECT_TRUE(it.isDone());
}

//*********************************Edge Case: Empty vector*************************
TEST(PlantIteratorTest, EmptyVector){
    vector<Plant*>empty;
    PlantIterator it(empty);

    it.first();
    EXPECT_TRUE(it.isDone());
    EXPECT_EQ(it.currentItem(), nullptr);
}

TEST(ChatIteratorTest, EmptyVector){
    vector<string>empty;
    ChatIterator it(&empty);

    it.first();
    EXPECT_TRUE(it.isDone());
    EXPECT_EQ(it.currentItem(), "");
}

int main(int argc,char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}