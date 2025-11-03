#include <gtest/gtest.h>
#include "ConcretePlantBuilder.h"

class TestPlant : public Plant{
public:
	TestPlant(const std::string& type, double price)
		: Plant("green", nullptr, price), type_(type) {}

	virtual Plant* clone() override { return new TestPlant(*this); }
	virtual void print() override {}
	virtual void add(Plant& plant) override {}
	virtual void remove(Plant& plant) override {}
	virtual Plant* getChild(string tag) override { return nullptr; }
	virtual std::string getType() const override { return type_; }

private:
	std::string type_;
};

TEST(ConcretePlantBuilderTest, EmptyInputReturnsNull){
	ConcretePlantBuilder builder;
	std::string dec = "";
	std::vector<Plant*> empty;
	Plant* p = builder.buildCompositePlant(empty, dec);
	EXPECT_EQ(p, nullptr);
}

TEST(ConcretePlantBuilderTest, SinglePlantNoDecoratorReturnsSamePointer){
	ConcretePlantBuilder builder;
	TestPlant* p1 = new TestPlant("Rose", 9.99);
	std::vector<Plant*> plants = { p1 };
	std::string dec = "";
	Plant* result = builder.buildCompositePlant(plants, dec);

	EXPECT_EQ(result, p1);

	delete p1;
}

TEST(ConcretePlantBuilderTest, SinglePlantWithWrapReturnsDecorator){
	ConcretePlantBuilder builder;
	TestPlant* p1 = new TestPlant("Tulip", 5.50);
	std::vector<Plant*> plants = { p1 };
	std::string dec = "wrap";
	Plant* result = builder.buildCompositePlant(plants, dec);

	ASSERT_NE(result, nullptr);
	EXPECT_NE(result, p1);

	std::string t = result->getType();
	EXPECT_NE(t.find("Tulip"), std::string::npos);

	delete result;
	delete p1;
}

TEST(ConcretePlantBuilderTest, MultiplePlantsWithPotReturnsGroupWrapped){
	ConcretePlantBuilder builder;
	TestPlant* p1 = new TestPlant("A", 1.0);
	TestPlant* p2 = new TestPlant("B", 2.0);
	std::vector<Plant*> plants = { p1, p2 };
	std::string dec = "pot";

	Plant* result = builder.buildCompositePlant(plants, dec);
	ASSERT_NE(result, nullptr);

	EXPECT_NE(result, p1);
	EXPECT_NE(result, p2);

	std::string t = result->getType();
	EXPECT_NE(t.find("A"), std::string::npos);
	EXPECT_NE(t.find("B"), std::string::npos);

	delete result; 
	delete p1;
	delete p2;
}


