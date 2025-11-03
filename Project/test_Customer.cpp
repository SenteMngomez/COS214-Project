#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Customer.h"
#include "Section.h"

//Mock Section class for testing
class MockSection : public Section {
public:
    MockSection(std::string name):Section(name){}
    
    void notify(Person* person) override{
        // Simple mock implementation - just record that notify was called
        notifyCalled=true;
        lastSender=person;
    }
    
    bool notifyCalled=false;
    Person* lastSender=nullptr;
};

class MockPerson:public Person {
public:
    MockPerson(std::string name):Person(name) {}
    
    void receiveMessage(Person* person, Section* section) override {
        
        lastSender=person;
        lastSection=section;
        receivedMessage=true;
    }
    
    Person* lastSender=nullptr;
    Section* lastSection=nullptr;
    bool receivedMessage=false;
};

class CustomerTest : public ::testing::Test {
protected:
    void SetUp() override {
        customer = new Customer("Rigby");
        mockSection = new MockSection("Test Room");
        mockSender = new MockPerson("Mordecai");

		mockSender->addSection(mockSection);
		mockSection->addPerson(mockSender);
        
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        std::cout.rdbuf(originalCoutBuffer);

		mockSection->removePerson(mockSender);
		mockSection->removePerson(customer);
        
        delete customer;
        delete mockSection;
        delete mockSender;
    }
    
    Customer* customer;
    MockSection* mockSection;
    MockPerson* mockSender;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(CustomerTest, ConstructorSetsName) {
    EXPECT_EQ(customer->getName(), "Rigby");
}

TEST_F(CustomerTest, ReceiveMessageIgnoresPurchaseType) {
    //Set up sender with Purchase message. Customer should ignore it.
    mockSender->sendMessage("Buy plants", "Purchase");
    
    customer->receiveMessage(mockSender, mockSection);
    
    //Should produce no output
    std::string output = outputStream.str();
    EXPECT_TRUE(output.empty());
}

TEST_F(CustomerTest, ReceiveMessageIgnoresCareType) {
    //Set up sender with Care message. Customer should ignore it
    mockSender->sendMessage("Water plants", "Care");
    
    customer->receiveMessage(mockSender, mockSection);
    
    //Should produce no output
    std::string output = outputStream.str();
    EXPECT_TRUE(output.empty());
}

TEST_F(CustomerTest, ReceiveMessageProcessesOtherTypes) {
    //Set up sender with Help message. Customer should process it
    mockSender->sendMessage("Need assistance", "Help");
    
    customer->receiveMessage(mockSender, mockSection);
    
    std::string output = outputStream.str();
    std::string expectedOutput = "[Test Room] Rigby received --Help-- \"Need assistance\" from Mordecai\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(CustomerTest, ReceiveMessageProcessesPurchaseComplete) {
    //Set up sender with Purchase Complete message. Customer should process it.
    mockSender->sendMessage("Purchase successful", "Purchase Complete");
    
    customer->receiveMessage(mockSender, mockSection);
    
    std::string output = outputStream.str();
    std::string expectedOutput = "[Test Room] Rigby received --Purchase Complete-- \"Purchase successful\" from Mordecai\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(CustomerTest, ReceiveMessageWithCustomMessageType) {
    // Set up sender with custom message type
    mockSender->sendMessage("Custom message", "Notification");
    
    // Customer should process custom message types
    customer->receiveMessage(mockSender, mockSection);
    
    // Should produce output
    std::string output = outputStream.str();
    std::string expectedOutput = "[Test Room] Rigby received --Notification-- \"Custom message\" from Mordecai\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(CustomerTest, InheritsFromPerson){
    // Test that Customer properly inherits from Person
    Person* person = customer;
    EXPECT_EQ(person->getName(), "Rigby");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}