#include <gtest/gtest.h>
#include "Inventory.h"
#include "FlowerFactory.h"
#include "SucculentFactory.h"

class InventoryTest : public ::testing::Test {
    protected:
        Inventory* inventory;
        FlowerFactory flowerFactory;
        SucculentFactory succulentFactory;

        void SetUp() override {
            inventory = Inventory::instance();
        }

};

TEST_F(InventoryTest, SingletonInstance) {

    Inventory* inv1 = Inventory::instance();
    Inventory* inv2 = Inventory::instance();

    EXPECT_EQ(inv1, inv2);

}

TEST_F(InventoryTest, UpdateInventory) {

    Plant* rose = flowerFactory.createPlant("Rose");
    ASSERT_NE(rose, nullptr);

    EXPECT_NO_THROW(inventory->updateInventory(rose));

}

TEST_F(InventoryTest, UpdateInventory) {

    EXPECT_NO_THROW(inventory->addStock("Rose", 5));
    EXPECT_NO_THROW(inventory->addStock("Rose", 3));

}

TEST_F(InventoryTest, RemovePlant) {

    Plant* rose = flowerFactory.createPlant("Rose");
    inventory->updateInventory(rose);

    std::string tag = rose->getTag();
    Plant* removed = inventory->removePlant(tag);

    ASSERT_NE(removed, nullptr);
    EXPECT_EQ(removed->getTag(), tag);

}

TEST_F(InventoryTest, RemoveNonExistentPlant) {

    Plant* removed = inventory->removePlant("Test tag");

    EXPECT_EQ(removed, nullptr);

}

TEST_F(InventoryTest, MultipleProductsInventory) {

    Plant* rose = flowerFactory.createPlant("Rose");
    Plant* tulip = flowerFactory.createPlant("Tulip");
    Plant* cactus = succulentFactory.createPlant("Cactus");

    EXPECT_NO_THROW(inventory->updateInventory(rose));
    EXPECT_NO_THROW(inventory->updateInventory(tulip));
    EXPECT_NO_THROW(inventory->updateInventory(cactus));

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}