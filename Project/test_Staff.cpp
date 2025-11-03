#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Staff.h"
#include "Section.h"

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

//Mock Person class for testing message sending
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

//Concrete Staff implementation for testing
class TestStaff : public Staff {
public:
    TestStaff(std::string name) : Staff(name) {}
    
    void handleRequest(Person* person) override {
        handleRequestCalled = true;
        lastRequestPerson = person;
        
        Staff::handleRequest(person);
    }
    
    bool handleRequestCalled = false;
    Person* lastRequestPerson = nullptr;
};

class StaffTest : public ::testing::Test {
protected:
    void SetUp() override {
        staff = new TestStaff("Benson");
        successor = new TestStaff("Skips");
        mockSection = new MockSection("Staff Room");
        mockSender = new MockPerson("Finn");
        
        //Set up section relationships
        mockSender->addSection(mockSection);
        mockSection->addPerson(mockSender);
        
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        //Restore cout
        std::cout.rdbuf(originalCoutBuffer);
        
        mockSection->removePerson(mockSender);
        
        delete staff;
        delete successor;
        delete mockSection;
        delete mockSender;
    }
    
    TestStaff* staff;
    TestStaff* successor;
    MockSection* mockSection;
    MockPerson* mockSender;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(StaffTest, ConstructorInitializesSuccessorToNull) {
    //Staff should initialize successor to nullptr
	//Testing the behavior when no successor is set
    mockSender->sendMessage("Test request", "Help");
    staff->handleRequest(mockSender);
    
    //Should output "Request Unhandled" when no successor
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Request Unhandled") != std::string::npos);
}

TEST_F(StaffTest, SetSuccessorSetsCorrectSuccessor) {
    staff->setSuccessor(successor);
    
    //Test that successor is called when request can't be handled
    mockSender->sendMessage("Test request", "UnknownType");
    staff->handleRequest(mockSender);
    
    //The successor's handleRequest should be called
    EXPECT_TRUE(successor->handleRequestCalled);
    EXPECT_EQ(successor->lastRequestPerson, mockSender);
}

TEST_F(StaffTest, HandleRequestCallsSuccessorWhenCantHandle) {
    staff->setSuccessor(successor);
    
    //Send a request that staff can't handle
    mockSender->sendMessage("Unknown request", "UnknownType");
    staff->handleRequest(mockSender);
    
    EXPECT_TRUE(staff->handleRequestCalled);
    EXPECT_TRUE(successor->handleRequestCalled);
}

TEST_F(StaffTest, ReceiveMessageProcessesPurchaseType) {
    //Set up sender with Purchase message
	vector<std::string> plants={"1","2"};
    mockSender->sendMessage("Buy plants", "Purchase",&plants);
    
    //Staff should process Purchase messages
    staff->receiveMessage(mockSender, mockSection);
    
    //Should produce output for Purchase messages
    std::string output = outputStream.str();
    std::string expectedOutput = "[Staff Room] Benson received --Purchase request-- \"Buy plants\" from Finn\n\tPurchasing plants: Plant-1, Plant-2\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(StaffTest, ReceiveMessageProcessesCareType) {
    //Set up sender with Care message
	vector<std::string> plants={"1","2"};
    mockSender->sendMessage("Water plants", "Care",&plants);
    
    //Staff should process Care messages
    staff->receiveMessage(mockSender, mockSection);
    
    //Should produce output for Care messages
    std::string output = outputStream.str();
    std::string expectedOutput = "[Staff Room] Benson received --Care request-- \"Water plants\" from Finn\n\tPlants to care for: Plant-1, Plant-2\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(StaffTest, ReceiveMessageProcessesOtherTypes) {
    // Set up sender with Help message
    mockSender->sendMessage("Need assistance", "Help");
    
    // Staff should process Help messages
    staff->receiveMessage(mockSender, mockSection);
    
    // Should produce output showing staff received message
    std::string output = outputStream.str();
    std::string expectedOutput = "[Staff Room] Benson received --Help request-- \"Need assistance\" from Finn\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(StaffTest, ReceiveMessageIgnoresPurchaseComplete) {
    // Set up sender with Purchase Complete message
    mockSender->sendMessage("Purchase successful", "Purchase Complete");
    
    // Staff should ignore Purchase Complete messages
    staff->receiveMessage(mockSender, mockSection);
    
    // Should produce no output
    std::string output = outputStream.str();
    EXPECT_TRUE(output.empty());
}

TEST_F(StaffTest, ChainOfResponsibilityWithMultipleStaff) {
    //Create a chain: staff -> successor -> thirdStaff
    TestStaff* thirdStaff = new TestStaff("Pops");
    staff->setSuccessor(successor);
    successor->setSuccessor(thirdStaff);
    
    //Send request that none can handle specifically
    mockSender->sendMessage("Complex request", "UnknownType");
    staff->handleRequest(mockSender);
    
    //All three should have been called in the chain
    EXPECT_TRUE(staff->handleRequestCalled);
    EXPECT_TRUE(successor->handleRequestCalled);
    EXPECT_TRUE(thirdStaff->handleRequestCalled);
    
    delete thirdStaff;
}

TEST_F(StaffTest, InheritsFromPerson) {
    //Test that Staff properly inherits from Person
    Person* person=staff;
    EXPECT_EQ(person->getName(), "Benson");
}

TEST_F(StaffTest, CanSendMessages) {
    //Test that Staff can send messages as a Person
    staff->addSection(mockSection);
    mockSection->addPerson(staff);
    
    staff->sendMessage("Staff announcement", "Announcement");
    
    //Verify the message was set correctly
    EXPECT_EQ(staff->getMessage(), "Staff announcement");
    EXPECT_EQ(staff->getMessageType(), "Announcement");
    
    // Clean up
    mockSection->removePerson(staff);
}

//Test with different staff names
TEST(StaffBasicTest, DifferentNames) {
    TestStaff alice("Alice");
    TestStaff bob("Bob");
    
    EXPECT_EQ(alice.getName(), "Alice");
    EXPECT_EQ(bob.getName(), "Bob");
}

