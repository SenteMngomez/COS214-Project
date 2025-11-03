#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "SalesClerk.h"
#include "SellPlant.h"
#include "Section.h"
#include "Staff.h"
#include "Person.h"

//Mock Section class for testing
class MockSection : public Section {
public:
    MockSection(std::string name) : Section(name) {}
    
    void notify(Person* person) override {
        notifyCalled = true;
        lastSender = person;
    }
    
    bool notifyCalled = false;
    Person* lastSender = nullptr;
};


class MockPerson : public Person {
public:
    MockPerson(std::string name) : Person(name) {}
    
    void receiveMessage(Person* person, Section* section) override {
        lastSender = person;
        lastSection = section;
        receivedMessage = true;
    }
    
    Person* lastSender = nullptr;
    Section* lastSection = nullptr;
    bool receivedMessage = false;
};


class MockStaff : public Staff {
public:
    MockStaff(std::string name) : Staff(name) {}
    
    void handleRequest(Person* person) override {
        handleRequestCalled = true;
        lastRequestPerson = person;
        Staff::handleRequest(person);
    }
    
    bool handleRequestCalled = false;
    Person* lastRequestPerson = nullptr;
};

//Mock SellPlant command for testing
class MockSellPlant : public SellPlant {
public:
    MockSellPlant() : SellPlant(nullptr) {}
    
    void execute(vector<std::string>* tags, string decorator="") override {
        executeCalled = true;
        lastTags = tags;
        lastDecorator = decorator;
        
        // Simulate receipt generation
        receipt = "Receipt: Sold " + std::to_string(tags->size()) + " plants";
        if (!decorator.empty()) {
            receipt += " with " + decorator;
        }
    }
    
    string getReceipt() {
        return receipt;
    }
    
    bool executeCalled = false;
    vector<std::string>* lastTags = nullptr;
    string lastDecorator = "";
    string receipt = "";
};

class SalesClerkTest : public ::testing::Test {
protected:
    void SetUp() override {
        salesClerk = new SalesClerk("Mordecai");
        mockPerson = new MockPerson("Rigby");
        mockStaffSuccessor = new MockStaff("Skips");
        mockSellPlant = new MockSellPlant();
        mockSection = new MockSection("Sales Room");

		mockSection->addPerson(mockPerson);
		mockPerson->addSection(mockSection);
        
        // Set up the SellPlant command
        salesClerk->setSellPlantCommand(mockSellPlant);
        
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        std::cout.rdbuf(originalCoutBuffer);

		mockSection->removePerson(mockPerson);
        
        delete salesClerk;
        delete mockPerson;
        delete mockStaffSuccessor;
        delete mockSellPlant;
        delete mockSection;
    }
    
    SalesClerk* salesClerk;
    MockPerson* mockPerson;
    MockStaff* mockStaffSuccessor;
    MockSellPlant* mockSellPlant;
    MockSection* mockSection;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(SalesClerkTest, ConstructorSetsName) {
    EXPECT_EQ(salesClerk->getName(), "Mordecai");
}

TEST_F(SalesClerkTest, HandlesPurchaseRequests) {
    vector<std::string> plants = {"1", "2", "3"};
    mockPerson->sendMessage("Buy plants", "Purchase", &plants, "pot");
    
    salesClerk->handleRequest(mockPerson);
    
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("(Sales Clerk)Mordecai will assist Rigby with their Purchase request") != std::string::npos);
    
    //Should have called the SellPlant command
    EXPECT_TRUE(mockSellPlant->executeCalled);
    EXPECT_EQ(mockSellPlant->lastTags, &plants);
    EXPECT_EQ(mockSellPlant->lastDecorator, "pot");
}

TEST_F(SalesClerkTest, DelegatesNonPurchaseRequests) {
    salesClerk->setSuccessor(mockStaffSuccessor);
    
    mockPerson->sendMessage("Need help", "Help");
    salesClerk->handleRequest(mockPerson);
    
    //Should delegate to successor
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Passing on request to Skips") != std::string::npos);
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
    EXPECT_EQ(mockStaffSuccessor->lastRequestPerson, mockPerson);
}

TEST_F(SalesClerkTest, DelegatesCareRequests) {
    salesClerk->setSuccessor(mockStaffSuccessor);
    
    vector<std::string> plants = {"1", "2"};
    mockPerson->sendMessage("Water plants", "Care", &plants);
    salesClerk->handleRequest(mockPerson);
    
    //Should delegate Care requests to successor
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Passing on request to Skips") != std::string::npos);
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
}

TEST_F(SalesClerkTest, IgnoresEmptyPurchaseRequests) {
    vector<std::string> emptyPlants;
    mockPerson->sendMessage("Buy nothing", "Purchase", &emptyPlants);
    
    salesClerk->handleRequest(mockPerson);
    
    
    EXPECT_FALSE(mockSellPlant->executeCalled);
    
    //Should not output assistance message
    std::string output = outputStream.str();
    EXPECT_TRUE(output.empty());
}

TEST_F(SalesClerkTest, SellExecutesCommandCorrectly) {
    vector<std::string> plants = {"5", "10"};
    string decorator = "wrap";
    string customerName = "Finn";
    
    salesClerk->sell(&plants, decorator, customerName);
    
    //Should execute the command
    EXPECT_TRUE(mockSellPlant->executeCalled);
    EXPECT_EQ(mockSellPlant->lastTags, &plants);
    EXPECT_EQ(mockSellPlant->lastDecorator, decorator);
}

TEST_F(SalesClerkTest, SellWithoutCommandShowsError) {
    
    SalesClerk clerkWithoutCommand("Benson");
    
    vector<std::string> plants = {"1", "2"};
    clerkWithoutCommand.sell(&plants, "pot", "Jake");
    
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Unable to make sale\n") != std::string::npos);
}

TEST_F(SalesClerkTest, PurchaseCompleteCallsSendMessage) {
    
    salesClerk->addSection(mockSection);
    mockSection->addPerson(salesClerk);
    
    string receipt = "Receipt: 3 plants sold";
    string customerName = "Marceline";
    
    salesClerk->purchaseComplete(receipt, customerName);
    
    // Should set the message correctly
    EXPECT_EQ(salesClerk->getMessage(), receipt);
    EXPECT_EQ(salesClerk->getMessageType(), "Purchase Complete");
    EXPECT_EQ(salesClerk->getDecorator(), customerName);
    
    mockSection->removePerson(salesClerk);
}

TEST_F(SalesClerkTest, SetSellPlantCommandWorks) {
    MockSellPlant* newCommand = new MockSellPlant();
    salesClerk->setSellPlantCommand(newCommand);
    
    vector<std::string> plants = {"7", "8"};
    salesClerk->sell(&plants, "pot", "Princess Bubblegum");
    
    //Should use the new command
    EXPECT_TRUE(newCommand->executeCalled);
    EXPECT_FALSE(mockSellPlant->executeCalled);
    
    delete newCommand;
}

TEST_F(SalesClerkTest, FullPurchaseWorkflow) {
   
    salesClerk->addSection(mockSection);
    mockSection->addPerson(salesClerk);
    mockSection->addPerson(mockPerson);
    
    vector<std::string> plants = {"1", "2", "3"};
    mockPerson->sendMessage("Buy rare plants", "Purchase", &plants, "fancy_pot");
    
    salesClerk->handleRequest(mockPerson);
    
    std::string output = outputStream.str();
    
    //Should show assistance message
    EXPECT_TRUE(output.find("(Sales Clerk)Mordecai will assist Rigby with their Purchase request") != std::string::npos);
    
    //Should have executed the command
    EXPECT_TRUE(mockSellPlant->executeCalled);
    EXPECT_EQ(mockSellPlant->lastDecorator, "fancy_pot");
    
    //Should have sent purchase complete message
    EXPECT_EQ(salesClerk->getMessageType(), "Purchase Complete");
    EXPECT_EQ(salesClerk->getDecorator(), "Rigby");
    
    
    mockSection->removePerson(salesClerk);
    mockSection->removePerson(mockPerson);
}

TEST_F(SalesClerkTest, InheritsFromStaff) {
    
    Staff* staff = salesClerk;
    EXPECT_EQ(staff->getName(), "Mordecai");
}

TEST_F(SalesClerkTest, CanSetSuccessor) {
    //Test that SalesClerk can set successor like any Staff
    salesClerk->setSuccessor(mockStaffSuccessor);
    
    // Verify by testing delegation
    mockPerson->sendMessage("Unknown request", "UnknownType");
    salesClerk->handleRequest(mockPerson);
    
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
}


TEST(SalesClerkBasicTest, DifferentNames) {
    SalesClerk alice("Alice");
    SalesClerk bob("Bob");
    
    EXPECT_EQ(alice.getName(), "Alice");
    EXPECT_EQ(bob.getName(), "Bob");
}

