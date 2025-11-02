#include <gtest/gtest.h>
#include "SellPlant.h"
#include "WaterPlant.h"
#include "GIveSunlight.h"
#include "Greenhouse.h"
#include "SalesAssistance.h"
#include "BasicReceiptBuilder.h"
#include "ConcretePlantBuilder.h"

class TestPlant : public Plant{
public:
	TestPlant(const std::string& type, double price)
		: Plant("green", nullptr, price), type_(type) {}

	virtual Plant* clone() override { return new TestPlant(*this); }
	virtual void print() override {}
	virtual void add(Plant& plant) override {}
	virtual void remove(Plant& plant) override {}
	virtual Plant* getChild(int tag) override { return nullptr; }
	virtual std::string getType() const override { return type_; }
    
private:
// bool watered ;
	std::string type_;
};


class WaterPlantTest : public ::testing::Test {
protected:
    Greenhouse* greenhouse;
    WaterPlant* waterCommand;

    void SetUp() override {
        greenhouse = new Greenhouse("UnitTest Greenhouse");

        TestPlant* p1 = new TestPlant("PlantA", 10.0);
        TestPlant* p2 = new TestPlant("PlantB", 15.0);
        p1->setTag(1);
        p2->setTag(2);

        greenhouse->addPlant(p1);
        greenhouse->addPlant(p2);

        waterCommand = new WaterPlant();
        waterCommand->setGreenhouse(greenhouse);
    }

    void TearDown() override {
        delete waterCommand;
        delete greenhouse;
    }
};

TEST_F(WaterPlantTest, Execute_SinglePlant_NoCrash) {
    std::vector<int> tags = {1};
    EXPECT_NO_THROW(waterCommand->execute(&tags));
}

TEST_F(WaterPlantTest, Execute_MultiplePlants_NoCrash) {
    std::vector<int> tags = {1, 2};
    EXPECT_NO_THROW(waterCommand->execute(&tags));
}

TEST_F(WaterPlantTest, Execute_InvalidTag_NoCrash) {
    std::vector<int> tags = {999};
    EXPECT_NO_THROW(waterCommand->execute(&tags));
}

TEST_F(WaterPlantTest, Execute_NullTag_NoCrash) {
    EXPECT_NO_THROW(waterCommand->execute(NULL));
}


TEST_F(WaterPlantTest, Execute_EmptyList_NoCrash) {
    std::vector<int> tags;
    EXPECT_NO_THROW(waterCommand->execute(&tags));
}

class SellPlantTest : public ::testing::Test {
protected:
    Greenhouse* greenhouse;
    
    SalesAssistance* salesHelper;
    BasicReceiptBuilder* builder;
    SellPlant* sellCommand;

    void SetUp() override {
        greenhouse = new Greenhouse("UnitTest Greenhouse");
       

        TestPlant* p1 = new TestPlant("PlantA", 10.50);
        TestPlant* p2 = new TestPlant("PlantB", 5.25);
        std::vector<Plant*> plants = { p1, p2 };
        std::string seller = "TestSeller";

        p1->setTag(1);
        p2->setTag(2);

        builder = new BasicReceiptBuilder(const_cast<std::string&>(seller), plants);
        PlantBuilder* pb = new ConcretePlantBuilder();
        salesHelper = new SalesAssistance();
        salesHelper->setBuilder(builder);

        sellCommand = new SellPlant(pb);
        sellCommand->setGreenhouse(greenhouse);
        sellCommand->setSalesAssitance(salesHelper);

        // Add some plants to the greenhouse
        // greenhouse->addPlant(flowerFactory->createPlant("Rose"));
        // greenhouse->addPlant(succulentFactory->createPlant("Aloe"));
        // greenhouse->addPlant(treeFactory->createPlant("Oak"));
        greenhouse->addPlant(p1);
        greenhouse->addPlant(p2);
    }

    void TearDown() override {
        delete sellCommand;
        delete salesHelper;
        delete builder;
        
        delete greenhouse;
    }
};



TEST_F(SellPlantTest, Execute_SinglePlant_ReturnsReceipt){
    std::vector<int> tags = {1}; 

    sellCommand->execute(&tags, "wrap"); 
    
    std::string receipt = sellCommand->getReceipt();
    
    EXPECT_FALSE(receipt.empty());
    EXPECT_NE(receipt.find("RECEIPT"), std::string::npos)
        << "Receipt should contain the word 'Receipt'";
    
}

TEST_F(SellPlantTest, Execute_InvalidTag_NoReceipt){
    std::vector<int> tags = {999}; // non-existent tag

    sellCommand->execute(&tags); // perform the sale

    std::string receipt = sellCommand->getReceipt();

    EXPECT_TRUE(receipt.find("No receipt available") != std::string::npos ||
                receipt.empty())
        << "Should not produce a valid receipt for invalid tag";
}


TEST_F(SellPlantTest, Execute_MultiplePlants_GeneratesCompositeReceipt) {
    std::vector<int> tags = {1, 2};

    sellCommand->execute(&tags, "pot"); // perform sale with decorator

    std::string receipt = sellCommand->getReceipt();

    EXPECT_NE(receipt.find("PlantA"), std::string::npos);
    // EXPECT_NE(receipt.find("Aloe"), std::string::npos);
    // EXPECT_NE(receipt.find("Total"), std::string::npos);
}
class GiveSunLightTest : public ::testing::Test {
protected:
    Greenhouse* greenhouse;
    GiveSunlight* GiveSunlightCommand;

    void SetUp() override {
        greenhouse = new Greenhouse("UnitTest Greenhouse");

        TestPlant* p1 = new TestPlant("PlantA", 10.0);
        TestPlant* p2 = new TestPlant("PlantB", 15.0);
        p1->setTag(1);
        p2->setTag(2);

        greenhouse->addPlant(p1);
        greenhouse->addPlant(p2);

        GiveSunlightCommand = new GiveSunlight();
        GiveSunlightCommand->setGreenhouse(greenhouse);
    }

    void TearDown() override {
        delete GiveSunlightCommand;
        delete greenhouse;
    }
};

TEST_F(GiveSunLightTest, Execute_SinglePlant_NoCrash) {
    std::vector<int> tags = {1};
    EXPECT_NO_THROW(GiveSunlightCommand->execute(&tags));
}

TEST_F(GiveSunLightTest, Execute_MultiplePlants_NoCrash) {
    std::vector<int> tags = {1, 2};
    EXPECT_NO_THROW(GiveSunlightCommand->execute(&tags));
}

TEST_F(GiveSunLightTest, Execute_InvalidTag_NoCrash) {
    std::vector<int> tags = {999};
    EXPECT_NO_THROW(GiveSunlightCommand->execute(&tags));
}

TEST_F(GiveSunLightTest, Execute_NullTag_NoCrash) {
    EXPECT_NO_THROW(GiveSunlightCommand->execute(NULL));
}

