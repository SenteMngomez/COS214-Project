#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "SalesRoom.h"
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

//Test helper to track Staff behavior without inheritance issues
class SalesStaffTracker {
public:
    static bool handleRequestCalled;
    static Person* lastRequestPerson;
    static std::vector<std::pair<Person*, Section*>> receivedMessages;
    static Person* lastSender;
    static Section* lastSection;
    
    static void reset() {
        handleRequestCalled = false;
        lastRequestPerson = nullptr;
        receivedMessages.clear();
        lastSender = nullptr;
        lastSection = nullptr;
    }
    
    static void recordMessage(Person* sender, Section* section) {
        receivedMessages.push_back({sender, section});
        lastSender = sender;
        lastSection = section;
    }
    
    static int getReceivedMessagesCount() {
        return receivedMessages.size();
    }
    
    static Person* getLastSender() {
        return lastSender;
    }
    
    static Section* getLastSection() {
        return lastSection;
    }
    
    static Person* getLastRequestPerson() {
        return lastRequestPerson;
    }
};

bool SalesStaffTracker::handleRequestCalled = false;
Person* SalesStaffTracker::lastRequestPerson = nullptr;
std::vector<std::pair<Person*, Section*>> SalesStaffTracker::receivedMessages = {};
Person* SalesStaffTracker::lastSender = nullptr;
Section* SalesStaffTracker::lastSection = nullptr;

//Test Staff class that tracks calls without virtual override issues
class TestSalesStaff : public Staff {
public:
    TestSalesStaff(std::string name) : Staff(name) {}
    
    void handleRequest(Person* person) override {
        SalesStaffTracker::handleRequestCalled = true;
        SalesStaffTracker::lastRequestPerson = person;
        // Provide the expected output format that tests are looking for
        std::cout << getName() << " handling request from " << person->getName() << std::endl;
    }
    
    void receiveMessage(Person* person, Section* section) override {
        SalesStaffTracker::recordMessage(person, section);
        Staff::receiveMessage(person, section);
    }
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

class SalesRoomTest : public ::testing::Test {
protected:
    void SetUp() override {
        salesRoom = new SalesRoom("Sales Room");
        customer1 = new MockCustomer("Finn");
        customer2 = new MockCustomer("Jake");
        staff1 = new TestSalesStaff("Mordecai");
        staff2 = new TestSalesStaff("Rigby");
        admin = new TestSalesStaff("Benson");
        
        // Reset static tracker
        SalesStaffTracker::reset();
        
        // Redirect cout to capture output
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(originalCoutBuffer);
        
        delete salesRoom;
        delete customer1;
        delete customer2;
        delete staff1;
        delete staff2;
        delete admin;
    }
    
    SalesRoom* salesRoom;
    MockCustomer* customer1;
    MockCustomer* customer2;
    TestSalesStaff* staff1;
    TestSalesStaff* staff2;
    TestSalesStaff* admin;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(SalesRoomTest, ConstructorSetsNameAndType) {
    EXPECT_EQ(salesRoom->getName(), "Sales Room");
    EXPECT_EQ(salesRoom->getType(), "Sales");
}

TEST_F(SalesRoomTest, InheritsFromSection) {
    //Testing that SalesRoom properly inherits from Section
    Section* section = salesRoom;
    EXPECT_EQ(section->getName(), "Sales Room");
    EXPECT_EQ(section->getType(), "Sales");
}

TEST_F(SalesRoomTest, NotifyRegularMessageBroadcastsToAll) {
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(customer2);
    salesRoom->addPerson(staff1);
    
    customer1->addSection(salesRoom);
    customer1->sendMessage("Hello everyone", "Help");
    
    //All other persons should receive the message
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(SalesStaffTracker::getReceivedMessagesCount(), 1); // staff1 received 1 message
    EXPECT_EQ(customer1->receivedMessages.size(), 0);//Sender doesn't receive own message
    
    //Verify everyone received the right message
    EXPECT_EQ(customer2->lastSender, customer1);
    EXPECT_EQ(SalesStaffTracker::getLastSender(), customer1);
    EXPECT_EQ(customer2->lastSection, salesRoom);
    EXPECT_EQ(SalesStaffTracker::getLastSection(), salesRoom);
}

TEST_F(SalesRoomTest, NotifyAddsMessageToHistory) {
    salesRoom->addPerson(customer1);
    customer1->addSection(salesRoom);
    
    customer1->sendMessage("Historic message", "Purchase");
    
    std::string history = salesRoom->getHistory();
    EXPECT_TRUE(history.find("Finn: Historic message") != std::string::npos);
    EXPECT_TRUE(history.find("Sales Room history") != std::string::npos);
}

TEST_F(SalesRoomTest, NotifyWithAdminCallsAdminHandleRequest) {
    salesRoom->setAdmin(admin);
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(staff1);
    
    customer1->addSection(salesRoom);
	vector<std::string> plants={"1","2"};
    customer1->sendMessage("I need flowers", "Purchase",&plants);
    
    //Admin should handle the request - check output for admin handling
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Benson handling request from Finn") != std::string::npos);
    EXPECT_EQ(SalesStaffTracker::getLastRequestPerson(), customer1);
    
    //Others should still receive the message
    EXPECT_EQ(SalesStaffTracker::getReceivedMessagesCount(), 1); // staff1 received message
    EXPECT_EQ(SalesStaffTracker::getLastSender(), customer1);
}

TEST_F(SalesRoomTest, NotifyWithoutAdminCallsFirstStaffHandleRequest) {
    //Don't set admin
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(customer2);
    salesRoom->addPerson(staff1);
    salesRoom->addPerson(staff2);
    
    customer1->addSection(salesRoom);
    customer1->sendMessage("Need assistance", "Purchase");
    
    //Check that staff1 handled the request (first staff)
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Mordecai handling request from Finn") != std::string::npos);
    EXPECT_FALSE(output.find("Rigby handling request from Finn") != std::string::npos); // staff2 should NOT handle
    
    EXPECT_EQ(SalesStaffTracker::getLastRequestPerson(), customer1);
    
    // All staff receive messages, customers except sender receive messages
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(SalesStaffTracker::getReceivedMessagesCount(), 2); // both staff received message
}

TEST_F(SalesRoomTest, NotifyWithoutAdminOrStaffDoesNotCrash) {
    //Add only customers, no staff or admin
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(customer2);
    
    customer1->addSection(salesRoom);
    customer1->sendMessage("I buy", "Purchase");
    
    //Should broadcast to other customers
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(customer2->lastSender, customer1);
    
    //Should add to history
    std::string history = salesRoom->getHistory();
    EXPECT_TRUE(history.find("Finn: I buy") != std::string::npos);
}

TEST_F(SalesRoomTest, PurchaseCompleteNotifiesSpecificCustomer) {
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(customer2);
    salesRoom->addPerson(staff1);
    
    //Staff sends Purchase Complete message with customer's name as decorator
    staff1->addSection(salesRoom);
    staff1->sendMessage("Your order is ready", "Purchase Complete", nullptr, "Finn");
    
    //Only customer1 (Finn) should receive the message
    EXPECT_EQ(customer1->receivedMessages.size(), 1);
    EXPECT_EQ(customer2->receivedMessages.size(), 0);
    EXPECT_EQ(SalesStaffTracker::getReceivedMessagesCount(), 0); // sender doesn't receive own message
    
    //Verify customer1 received the correct message
    EXPECT_EQ(customer1->lastSender, staff1);
    EXPECT_EQ(customer1->lastSection, salesRoom);
}

TEST_F(SalesRoomTest, PurchaseCompleteWithUnknownCustomerName) {
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(customer2);
    salesRoom->addPerson(staff1);
    
    //Staff sends Purchase Complete with non-existent customer name
    staff1->addSection(salesRoom);
    staff1->sendMessage("Order ready", "Purchase Complete", nullptr, "NonExistentCustomer");
    
    //No customers should receive the message
    EXPECT_EQ(customer1->receivedMessages.size(), 0);
    EXPECT_EQ(customer2->receivedMessages.size(), 0);
    
    //Should still add to history
    std::string history = salesRoom->getHistory();
    EXPECT_TRUE(history.find("Mordecai: Order ready") != std::string::npos);
}

TEST_F(SalesRoomTest, PurchaseCompleteAddsToHistoryAndReturns) {
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(staff1);
    salesRoom->setAdmin(admin);
    
    staff1->addSection(salesRoom);
    staff1->sendMessage("Purchase completed", "Purchase Complete", nullptr, "Finn");
    
    //Should add to history
    std::string history = salesRoom->getHistory();
    EXPECT_TRUE(history.find("Mordecai: Purchase completed") != std::string::npos);
    
    //Admin should not handle Purchase Complete requests  
    EXPECT_FALSE(SalesStaffTracker::handleRequestCalled);
}

TEST_F(SalesRoomTest, EmptyRoomNotifiesNobody) {
    //Add only sender to room
    salesRoom->addPerson(customer1);
    
    customer1->addSection(salesRoom);
    customer1->sendMessage("Talking to myself", "Help");
    
    //Nobody else to receive message
    EXPECT_EQ(customer1->receivedMessages.size(), 0);
    
    //Should still add to history
    std::string history = salesRoom->getHistory();
    EXPECT_TRUE(history.find("Finn: Talking to myself") != std::string::npos);
}

TEST_F(SalesRoomTest, MixedPersonTypesReceiveMessages) {
    salesRoom->addPerson(customer1);
    salesRoom->addPerson(staff1);
    salesRoom->addPerson(customer2);
    
    staff1->addSection(salesRoom);
    staff1->sendMessage("Store announcement", "Announcement");
    
    EXPECT_EQ(customer1->receivedMessages.size(), 1);
    EXPECT_EQ(customer2->receivedMessages.size(), 1);
    EXPECT_EQ(SalesStaffTracker::getReceivedMessagesCount(), 0); //Sender doesn't receive own message
    
    //Verify message details
    EXPECT_EQ(customer1->lastSender, staff1);
    EXPECT_EQ(customer2->lastSender, staff1);
}

TEST_F(SalesRoomTest, AdminPriorityOverStaff) {
    salesRoom->setAdmin(admin);
    salesRoom->addPerson(admin); // Add admin to personList so they receive messages
    salesRoom->addPerson(staff1);
    salesRoom->addPerson(staff2);
    salesRoom->addPerson(customer1);
    
    customer1->addSection(salesRoom);
    customer1->sendMessage("Need manager", "Help");
    
    //Admin should handle request, not staff - check output
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Benson handling request from Finn") != std::string::npos);
    EXPECT_FALSE(output.find("Mordecai handling request from Finn") != std::string::npos);
    EXPECT_FALSE(output.find("Rigby handling request from Finn") != std::string::npos);
    
    //All should still receive the message
    EXPECT_EQ(SalesStaffTracker::getReceivedMessagesCount(), 3); // admin + 2 staff received messages
}

TEST_F(SalesRoomTest, PurchaseCompleteWithMultipleMatchingNames) {
    //Add two customers with same name
    MockCustomer* customer3 = new MockCustomer("Finn");
    salesRoom->addPerson(customer1); //Also named "Finn"
    salesRoom->addPerson(customer3);
    salesRoom->addPerson(staff1);
    
    staff1->addSection(salesRoom);
    staff1->sendMessage("Order ready", "Purchase Complete", nullptr, "Finn");
    
    //Only first matching customer should receive message
    EXPECT_EQ(customer1->receivedMessages.size(), 1);
    EXPECT_EQ(customer3->receivedMessages.size(), 0);
    
    delete customer3;
}

TEST_F(SalesRoomTest, GetHistoryInheritsFromSection) {
    salesRoom->addPerson(customer1);
    customer1->addSection(salesRoom);
    
    //Testing empty history
    std::string emptyHistory = salesRoom->getHistory();
    EXPECT_TRUE(emptyHistory.find("Sales Room has no message history") != std::string::npos);
    
    //Testing with messages
    customer1->sendMessage("First message", "Help");
    customer1->sendMessage("Second message", "Purchase");
    
    std::string history = salesRoom->getHistory();
    EXPECT_TRUE(history.find("========Sales Room history========") != std::string::npos);
    EXPECT_TRUE(history.find("Finn: First message") != std::string::npos);
    EXPECT_TRUE(history.find("Finn: Second message") != std::string::npos);
}

//Test with different sales room names
TEST(SalesRoomBasicTest, DifferentNames) {
    SalesRoom mainSales("Main Sales Floor");
    SalesRoom plantSales("Plant Sales Corner");
    
    EXPECT_EQ(mainSales.getName(), "Main Sales Floor");
    EXPECT_EQ(plantSales.getName(), "Plant Sales Corner");
    EXPECT_EQ(mainSales.getType(), "Sales");
    EXPECT_EQ(plantSales.getType(), "Sales");
}

