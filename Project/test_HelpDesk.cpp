#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "HelpDesk.h"
#include "Person.h"
#include "Staff.h"
#include "Customer.h"

//Mock Person class for testing
class MockPerson : public Person {
public:
    MockPerson(std::string name) : Person(name) {}
    
    void receiveMessage(Person* person, Section* section) override {
        receivedMessages.push_back({person, section});
        lastSender = person;
        lastSection = section;
    }
    
    struct ReceivedMessage {
        Person* sender;
        Section* section;
    };
    
    std::vector<ReceivedMessage> receivedMessages;
    Person* lastSender = nullptr;
    Section* lastSection = nullptr;
};

//Mock Staff class for testing
class MockStaff : public Staff {
public:
    MockStaff(std::string name) : Staff(name) {}
    
    void handleRequest(Person* person) override {
        handleRequestCalled = true;
        lastRequestPerson = person;
        Staff::handleRequest(person);
    }
    
    void receiveMessage(Person* person, Section* section) override {
        receivedMessages.push_back({person, section});
        lastSender = person;
        lastSection = section;
    }
    
    struct ReceivedMessage {
        Person* sender;
        Section* section;
    };
    
    bool handleRequestCalled = false;
    Person* lastRequestPerson = nullptr;
    std::vector<ReceivedMessage> receivedMessages;
    Person* lastSender = nullptr;
    Section* lastSection = nullptr;
};

//Mock Customer class for testing
class MockCustomer : public Customer {
public:
    MockCustomer(std::string name) : Customer(name) {}
    
    void receiveMessage(Person* person, Section* section) override {
        receivedMessages.push_back({person, section});
        lastSender = person;
        lastSection = section;
    }
    
    struct ReceivedMessage {
        Person* sender;
        Section* section;
    };
    
    std::vector<ReceivedMessage> receivedMessages;
    Person* lastSender = nullptr;
    Section* lastSection = nullptr;
};

class HelpDeskTest : public ::testing::Test {
protected:
    void SetUp() override {
        helpDesk = new HelpDesk("Help Desk");
        customer1 = new MockCustomer("Finn");
        customer2 = new MockCustomer("Jake");
        staff1 = new MockStaff("Marceline");
        staff2 = new MockStaff("Bubblegum");
        admin = new MockStaff("Ice King");
        
        // Redirect cout to capture output
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(originalCoutBuffer);
        
        delete helpDesk;
        delete customer1;
        delete customer2;
        delete staff1;
        delete staff2;
        delete admin;
    }
    
    HelpDesk* helpDesk;
    MockCustomer* customer1;
    MockCustomer* customer2;
    MockStaff* staff1;
    MockStaff* staff2;
    MockStaff* admin;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(HelpDeskTest, ConstructorSetsNameAndType) {
    EXPECT_EQ(helpDesk->getName(), "Help Desk");
    EXPECT_EQ(helpDesk->getType(), "Help");
}

TEST_F(HelpDeskTest, InheritsFromSection) {
    // Test that HelpDesk properly inherits from Section
    Section* section = helpDesk;
    EXPECT_EQ(section->getName(), "Help Desk");
    EXPECT_EQ(section->getType(), "Help");
}

TEST_F(HelpDeskTest, NotifyRejectsPurchaseMessage) {
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(staff1);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("Buy plants", "Purchase");
    
    //Should output error message
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Cannot send Purchase message in Help room") != std::string::npos);
    
    //Nobody should receive the message
    EXPECT_EQ(staff1->receivedMessages.size(), 0);
    EXPECT_EQ(customer1->receivedMessages.size(), 0);
    
    //Should not handle request
    EXPECT_FALSE(staff1->handleRequestCalled);
    
    //Should not add to history
    std::string history = helpDesk->getHistory();
    EXPECT_FALSE(history.find("Finn: Buy plants") != std::string::npos);
}

TEST_F(HelpDeskTest, NotifyRejectsPurchaseCompleteMessage) {
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(staff1);
    
    staff1->addSection(helpDesk);
    staff1->sendMessage("Purchase finished", "Purchase Complete");
    
    //Should output error message
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Cannot send Purchase Complete message in Help room") != std::string::npos);
    
    //Nobody should receive the message
    EXPECT_EQ(customer1->receivedMessages.size(), 0);
    EXPECT_EQ(staff1->receivedMessages.size(), 0);
    
    //Should not handle request
    EXPECT_FALSE(staff1->handleRequestCalled);
}

TEST_F(HelpDeskTest, NotifyAcceptsHelpMessage) {
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(customer2);
    helpDesk->addPerson(staff1);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("I need assistance", "Help");
    
    std::string output = outputStream.str();
    EXPECT_FALSE(output.find("Cannot send") != std::string::npos);
    
    //All others should receive the message
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(staff1->receivedMessages.size(), 1);
    EXPECT_EQ(customer1->receivedMessages.size(), 0); //Sender doesn't receive own message
    
    //Verify message details
    EXPECT_EQ(customer2->lastSender, customer1);
    EXPECT_EQ(staff1->lastSender, customer1);
    EXPECT_EQ(customer2->lastSection, helpDesk);
    EXPECT_EQ(staff1->lastSection, helpDesk);
}

TEST_F(HelpDeskTest, NotifyAcceptsCareMessage) {
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(staff1);
    
    customer1->addSection(helpDesk);
    std::vector<std::string> plants = {"1", "2", "3"};
    customer1->sendMessage("Help with plant care", "Care", &plants);
    
    //Should not output error message
    std::string output = outputStream.str();
    EXPECT_FALSE(output.find("Cannot send") != std::string::npos);
    
    //Staff should receive the message
    EXPECT_EQ(staff1->receivedMessages.size(), 1);
    EXPECT_EQ(staff1->lastSender, customer1);
}

TEST_F(HelpDeskTest, NotifyAddsToHistoryForValidMessages) {
    helpDesk->addPerson(customer1);
    customer1->addSection(helpDesk);
    
    customer1->sendMessage("Help request", "Help");
    
    std::string history = helpDesk->getHistory();
    EXPECT_TRUE(history.find("Finn: Help request") != std::string::npos);
    EXPECT_TRUE(history.find("Help Desk history") != std::string::npos);
}

TEST_F(HelpDeskTest, NotifyDoesNotAddToHistoryForRejectedMessages) {
    helpDesk->addPerson(customer1);
    customer1->addSection(helpDesk);
    
    customer1->sendMessage("Invalid purchase", "Purchase");
    
    std::string history = helpDesk->getHistory();
    EXPECT_FALSE(history.find("Finn: Invalid purchase") != std::string::npos);
    EXPECT_TRUE(history.find("Help Desk has no message history") != std::string::npos);
}

TEST_F(HelpDeskTest, NotifyWithAdminCallsAdminHandleRequest) {
    helpDesk->setAdmin(admin);
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(staff1);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("Need manager", "Help");
    
    //Admin should handle the request
    EXPECT_TRUE(admin->handleRequestCalled);
    EXPECT_EQ(admin->lastRequestPerson, customer1);
    
    //Staff should not handle the request
    EXPECT_FALSE(staff1->handleRequestCalled);
    
    //All should still receive the message
    EXPECT_EQ(staff1->receivedMessages.size(), 1);
}

TEST_F(HelpDeskTest, NotifyWithoutAdminCallsFirstStaffHandleRequest) {
    
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(customer2);
    helpDesk->addPerson(staff1);
    helpDesk->addPerson(staff2);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("Need help", "Help");
    
    //First staff should handle the request
    EXPECT_TRUE(staff1->handleRequestCalled);
    EXPECT_EQ(staff1->lastRequestPerson, customer1);
    
    //Second staff should not handle the request
    EXPECT_FALSE(staff2->handleRequestCalled);
    
    //All should receive the message
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(staff1->receivedMessages.size(), 1);
    EXPECT_EQ(staff2->receivedMessages.size(), 1);
}

TEST_F(HelpDeskTest, NotifyWithoutAdminOrStaffDoesNotCrash) {
    //Add only customers, no staff or admin
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(customer2);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("Help me", "Help");
    
    //Should broadcast to other customers
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(customer2->lastSender, customer1);
    
    //Should add to history
    std::string history = helpDesk->getHistory();
    EXPECT_TRUE(history.find("Finn: Help me") != std::string::npos);
}

TEST_F(HelpDeskTest, NotifyBroadcastsToAllExceptSender) {
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(customer2);
    helpDesk->addPerson(staff1);
    helpDesk->addPerson(staff2);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("Hello everyone", "Help");
    
    //All except sender should receive the message
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(staff1->receivedMessages.size(), 1);
    EXPECT_EQ(staff2->receivedMessages.size(), 1);
    EXPECT_EQ(customer1->receivedMessages.size(), 0); //Sender doesn't receive own
    
    //Verify all received the same message
    EXPECT_EQ(customer2->lastSender, customer1);
    EXPECT_EQ(staff1->lastSender, customer1);
    EXPECT_EQ(staff2->lastSender, customer1);
}

TEST_F(HelpDeskTest, MultipleStaffMembersOnlyFirstHandlesRequest) {
    helpDesk->addPerson(staff1);
    helpDesk->addPerson(staff2);
    helpDesk->addPerson(customer1);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("Help request", "Help");
    
    //Only first staff should handle request due to break statement
    EXPECT_TRUE(staff1->handleRequestCalled);
    EXPECT_FALSE(staff2->handleRequestCalled);
    
    // Both should receive the message
    EXPECT_EQ(staff1->receivedMessages.size(), 1);
    EXPECT_EQ(staff2->receivedMessages.size(), 1);
}

// TEST_F(HelpDeskTest, AcceptsVariousMessageTypes) {
//     helpDesk->addPerson(customer1);
//     helpDesk->addPerson(staff1);
    
//     customer1->addSection(helpDesk);
    
//     //Test various acceptable message types
//     std::vector<std::string> validTypes = {"Help", "Care", "Question", "Support", "Announcement"};
    
//     for (const std::string& type : validTypes) {
//         customer1->sendMessage("Test message", type);
        
//         std::string output = outputStream.str();
//         EXPECT_FALSE(output.find("Cannot send") != std::string::npos) 
//             << "Type '" << type << "' should be accepted";
        
//         //Clear output for next test
//         outputStream.str("");
//         outputStream.clear();
//     }
// }

TEST_F(HelpDeskTest, EmptyRoomNotifiesNobody) {
    //Add only sender to room
    helpDesk->addPerson(customer1);
    
    customer1->addSection(helpDesk);
    customer1->sendMessage("Talking to myself", "Help");
    
    //Nobody else to receive message
    EXPECT_EQ(customer1->receivedMessages.size(), 0);
    
    //Should still add to history
    std::string history = helpDesk->getHistory();
    EXPECT_TRUE(history.find("Finn: Talking to myself") != std::string::npos);
}

TEST_F(HelpDeskTest, MixedPersonTypesReceiveMessages) {
    helpDesk->addPerson(customer1);
    helpDesk->addPerson(staff1);
    helpDesk->addPerson(customer2);
    
    staff1->addSection(helpDesk);
    staff1->sendMessage("Staff announcement", "Announcement");
    
    //All customers should receive the message
    EXPECT_EQ(customer1->receivedMessages.size(), 1);
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(staff1->receivedMessages.size(), 0); //Sender doesn't receive own message
    
    //Verify message details
    EXPECT_EQ(customer1->lastSender, staff1);
    EXPECT_EQ(customer2->lastSender, staff1);
}

TEST_F(HelpDeskTest, GetHistoryInheritsFromSection) {
    helpDesk->addPerson(customer1);
    customer1->addSection(helpDesk);
    
    //Test empty history
    std::string emptyHistory = helpDesk->getHistory();
    EXPECT_TRUE(emptyHistory.find("Help Desk has no message history") != std::string::npos);
    
    //Test with messages
    customer1->sendMessage("First message", "Help");
    customer1->sendMessage("Second message", "Care");
    
    std::string history = helpDesk->getHistory();
    EXPECT_TRUE(history.find("========Help Desk history========") != std::string::npos);
    EXPECT_TRUE(history.find("Finn: First message") != std::string::npos);
    EXPECT_TRUE(history.find("Finn: Second message") != std::string::npos);
}

//Test with different help desk names
TEST(HelpDeskBasicTest, DifferentNames) {
    HelpDesk mainHelp("Main Help Desk");
    HelpDesk plantHelp("Plant Care Help");
    
    EXPECT_EQ(mainHelp.getName(), "Main Help Desk");
    EXPECT_EQ(plantHelp.getName(), "Plant Care Help");
    EXPECT_EQ(mainHelp.getType(), "Help");
    EXPECT_EQ(plantHelp.getType(), "Help");
}

