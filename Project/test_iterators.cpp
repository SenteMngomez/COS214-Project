#include <gtest/gtest.h>
#include "Plant.h"
#include "Section.h"
#include "Iterator.h"
#include "PlantIterator.h"
#include "ChatIterator.h"
#include <string>
#include <iostream>
using namespace std;

class MockPlant : public Plant{
    public:
        MockPlant(string colour):Plant(colour,nullptr,50.0){
            setTag(getType()+"#"+colour);
        }
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
    vector<Plant*> plants = {new MockPlant("red"),new MockPlant("purple"),new MockPlant("pink")};
    PlantIterator it(plants);
    it.first();
    EXPECT_EQ(it.currentItem()->getTag(), "MockPlant#pink");
    it.next();
    EXPECT_EQ(it.currentItem()->getTag(), "MockPlant#purple");
    it.next();
    EXPECT_EQ(it.currentItem()->getTag(), "MockPlant#red");
    it.next();
    EXPECT_TRUE(it.isDone());
    for (Plant* p : plants) delete p;
}

//****************************Chat Iterator Tests****************** 
TEST(ChatIteratorTest, IteratesCorrectly){
    vector<string> messages = {"Zane: Yoh this rose is nice","Lerato: I'd like to buy this","Amy: Heyyy"};
    ChatIterator it(&messages);

    it.first();
    EXPECT_EQ(it.currentItem(),"Amy: Heyyy");
    it.next();
    EXPECT_EQ(it.currentItem(),"Lerato: I'd like to buy this");
    it.next();
    EXPECT_EQ(it.currentItem(),"Zane: Yoh this rose is nice");
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

