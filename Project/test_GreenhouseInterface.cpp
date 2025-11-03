#include <gtest/gtest.h>
#include "GreenhouseInterface.h"
#include "Inventory.h"
#include "FlowerFactory.h"

class GreenhouseInterfaceTest : public ::testing::Test {

    protected:
        GreenhouseInterface greenhouse;
        Inventory* inventory;
        FlowerFactory factory;

        void SetUp() override {
            inventory = Inventory::instance();
        }

        

};

TEST_F(GreenhouseInterfaceTest, AttachObserver) {
    EXPECT_NO_THROW(greenhouse.attach(inventory));
}

TEST_F(GreenhouseInterfaceTest, DetachObserver) {
    greenhouse.attach(inventory);
    EXPECT_NO_THROW(greenhouse.detach(inventory));
}

TEST_F(GreenhouseInterfaceTest, NotifyObservers) {
    greenhouse.attach(inventory);

    Plant* rose = factory.createPlant("Rose");
    ASSERT_NE(rose, nullptr);

    EXPECT_NO_THROW(greenhouse.notify(rose));
}

