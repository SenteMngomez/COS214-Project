#include <gtest/gtest.h>
#include "BasicReceiptBuilder.h"

class TestPlant : public Plant {
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

TEST(BasicReceiptBuilderTest, BuildsReceiptWithItemsAndTotal) {
	TestPlant* p1 = new TestPlant("PlantA", 10.50);
	TestPlant* p2 = new TestPlant("PlantB", 5.25);
	std::vector<Plant*> plants = { p1, p2 };
	std::string seller = "TestSeller";

	BasicReceiptBuilder builder(const_cast<std::string&>(seller), plants);

	builder.addPrice();
	builder.addPlantDetails();
	builder.addSeller();
	Receipt* r = builder.getResult();

	ASSERT_NE(r, nullptr);
	std::string s = r->toString();
	EXPECT_NE(s.find("Seller: TestSeller"), std::string::npos);
	EXPECT_NE(s.find("PlantA"), std::string::npos);
	EXPECT_NE(s.find("PlantB"), std::string::npos);
	EXPECT_NE(s.find("Total: R"), std::string::npos);

	delete r;
	delete p1;
	delete p2;
}

TEST(BasicReceiptBuilderTest, EmptyPlantListProducesZeroTotal) {
	std::vector<Plant*> plants;
	std::string seller = "EmptySeller";
	BasicReceiptBuilder builder(const_cast<std::string&>(seller), plants);

	builder.addPrice();
	builder.addPlantDetails();
	builder.addSeller();
	Receipt* r = builder.getResult();

	ASSERT_NE(r, nullptr);
	std::string s = r->toString();
	EXPECT_NE(s.find("Seller: EmptySeller"), std::string::npos);
	EXPECT_NE(s.find("Total: R0"), std::string::npos);

	delete r;
}