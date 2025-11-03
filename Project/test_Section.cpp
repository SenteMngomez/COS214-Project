#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Section.h"
#include "Person.h"
#include "Staff.h"
#include "ChatIterator.h"
#include "Iterator.h"

//Concrete Section implementation for testing
class TestSection : public Section {
public:
    TestSection(std::string name) : Section(name) {
        type = "Test";
    }
    
    void notify(Person* person) override {
        notifyCalled = true;
        lastNotifiedPerson = person;
        notifyCallCount++;
        
        //Add to history like real sections do
        addToHistory(person);
        
        //Mock notification behavior - notify all other persons
        for (Person* p : personList) {
            if (p != person) {
                p->receiveMessage(person, this);
            }
        }
        
        //If admin exists, let admin handle the request
        if (admin) {
            admin->handleRequest(person);
        }
    }
    
    bool notifyCalled = false;
    Person* lastNotifiedPerson = nullptr;
    int notifyCallCount = 0;
};

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

// Mock Staff class for testing
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

class SectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        section = new TestSection("Test Room");
        person1 = new MockPerson("Finn");
        person2 = new MockPerson("Jake");
        person3 = new MockPerson("Marceline");
        admin = new MockStaff("Benson");
        
        //Redirect cout to capture output
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(originalCoutBuffer);
        
        delete section;
        delete person1;
        delete person2;
        delete person3;
        delete admin;
    }
    
    TestSection* section;
    MockPerson* person1;
    MockPerson* person2;
    MockPerson* person3;
    MockStaff* admin;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(SectionTest, ConstructorSetsName) {
    EXPECT_EQ(section->getName(), "Test Room");
    EXPECT_EQ(section->getType(), "Test");
}

TEST_F(SectionTest, ConstructorInitializesAdmin) {
    //Admin should be nullptr initially

    person1->addSection(section);
    section->addPerson(person1);
    
    person1->sendMessage("Test message", "Help");
    
    // Without admin, only notification should happen
    EXPECT_TRUE(section->notifyCalled);
}

TEST_F(SectionTest, AddPersonWorks) {
    section->addPerson(person1);
    section->addPerson(person2);
    
    //Test that persons are added by triggering notification
    person1->addSection(section);
    person1->sendMessage("Hello everyone", "Help");
    
    //person2 should receive the message but person1 should not receive their own message
    EXPECT_EQ(person2->receivedMessages.size(), 1);
    EXPECT_EQ(person2->lastSender, person1);
    EXPECT_EQ(person2->lastSection, section);
    
    //person1 should not receive their own message
    EXPECT_EQ(person1->receivedMessages.size(), 0);
}

TEST_F(SectionTest, RemovePersonWorks) {
    section->addPerson(person1);
    section->addPerson(person2);
    
    //Remove person1
    Person* removed = section->removePerson(person1);
    
    EXPECT_EQ(removed, person1);
    
    //Now when person2 sends a message, person1 shouldn't receive it
    person2->addSection(section);
    person2->sendMessage("After removal", "Help");
    
    EXPECT_EQ(person1->receivedMessages.size(), 0);
}

TEST_F(SectionTest, RemoveNonExistentPersonReturnsNull) {
    section->addPerson(person1);
    
    //Try to remove unadded person
    Person* removed = section->removePerson(person2);
    
    EXPECT_EQ(removed, nullptr);
}

TEST_F(SectionTest, SetAdminWorks) {
    section->setAdmin(admin);
    section->addPerson(person1);
    
    person1->addSection(section);
    person1->sendMessage("Need admin help", "Help");
    
    //Admin should handle the request
    EXPECT_TRUE(admin->handleRequestCalled);
    EXPECT_EQ(admin->lastRequestPerson, person1);
}

TEST_F(SectionTest, NotifyCallsAddToHistory) {
    section->addPerson(person1);
    person1->addSection(section);
    
    person1->sendMessage("Historic message", "Help");
    
    //Check that history contains the message
    std::string history = section->getHistory();
    EXPECT_TRUE(history.find("Finn: Historic message") != std::string::npos);
    EXPECT_TRUE(history.find("Test Room history") != std::string::npos);
}

TEST_F(SectionTest, NotifyWithMultiplePeople) {
    section->addPerson(person1);
    section->addPerson(person2);
    section->addPerson(person3);
    
    person1->addSection(section);
    person1->sendMessage("Message to all", "Help");
    
    EXPECT_EQ(person2->receivedMessages.size(), 1);
    EXPECT_EQ(person3->receivedMessages.size(), 1);
    EXPECT_EQ(person1->receivedMessages.size(), 0); //Sender doesn't receive own message
    
    //Check all received the same message
    EXPECT_EQ(person2->lastSender, person1);
    EXPECT_EQ(person3->lastSender, person1);
    EXPECT_EQ(person2->lastSection, section);
    EXPECT_EQ(person3->lastSection, section);
}

TEST_F(SectionTest, AddToHistoryIgnoresEmptyMessages) {
    section->addPerson(person1);
    person1->addSection(section);
    
    //Send empty message
    person1->sendMessage("", "Help");
    
    std::string history = section->getHistory();
    //Should only contain the header, no message content
    EXPECT_TRUE(history.find("Test Room has no message history\n") != std::string::npos);
    EXPECT_FALSE(history.find("Finn:") != std::string::npos);
}

TEST_F(SectionTest, AddToHistoryWithValidMessage) {
    section->addPerson(person1);
    person1->addSection(section);
    
    person1->sendMessage("Valid message", "Help");
    
    std::string history = section->getHistory();
    EXPECT_TRUE(history.find("========Test Room history========") != std::string::npos);
    EXPECT_TRUE(history.find("Finn: Valid message") != std::string::npos);
}

TEST_F(SectionTest, MultipleMessagesInHistory) {
    section->addPerson(person1);
    section->addPerson(person2);
    
    person1->addSection(section);
    person2->addSection(section);
    
    person1->sendMessage("First message", "Help");
    person2->sendMessage("Second message", "Purchase");
    
    std::string history = section->getHistory();
    EXPECT_TRUE(history.find("Finn: First message") != std::string::npos);
    EXPECT_TRUE(history.find("Jake: Second message") != std::string::npos);
}

TEST_F(SectionTest, CreateIteratorReturnsValidIterator) {
    section->addPerson(person1);
    person1->addSection(section);
    
    //Add some messages to history
    person1->sendMessage("Message 1", "Help");
    person1->sendMessage("Message 2", "Care");
    
    Iterator* iterator = section->createIterator();
    
    EXPECT_NE(iterator, nullptr);
    
    delete iterator;
}

TEST_F(SectionTest, GetHistoryFormatsCorrectly) {
    std::string history=section->getHistory();
    
    //Should contain formatted header even with no messages
    EXPECT_TRUE(history.find("Test Room has no message history\n") != std::string::npos);
}

TEST_F(SectionTest, GetNameReturnsCorrectName) {
    EXPECT_EQ(section->getName(), "Test Room");
    
    TestSection* anotherSection = new TestSection("Another Room");
    EXPECT_EQ(anotherSection->getName(), "Another Room");
    
    delete anotherSection;
}

TEST_F(SectionTest, GetTypeReturnsCorrectType) {
    EXPECT_EQ(section->getType(), "Test");
}

TEST_F(SectionTest, AdminAndPersonsBothReceiveNotification) {
    section->setAdmin(admin);
    section->addPerson(person1);
    section->addPerson(person2);
    
    person1->addSection(section);
    person1->sendMessage("Help request", "Help");
    
    //Admin should handle request
    EXPECT_TRUE(admin->handleRequestCalled);
    EXPECT_EQ(admin->lastRequestPerson, person1);
    
    //Other person should still receive message
    EXPECT_EQ(person2->receivedMessages.size(), 1);
    EXPECT_EQ(person2->lastSender, person1);
}

TEST_F(SectionTest, DestructorClearsContainers) {
    section->addPerson(person1);
    person1->addSection(section);
    person1->sendMessage("Test message", "Help");
    
    // Delete section (destructor should run cleanly)
    delete section;
    section = nullptr;
    
    // Test passes if no crashes occur
    SUCCEED();
}

//Test section with different names and types
TEST(SectionBasicTest, DifferentNamesAndTypes) {
    TestSection salesRoom("Sales Room");
    TestSection helpDesk("Help Desk");
    
    EXPECT_EQ(salesRoom.getName(), "Sales Room");
    EXPECT_EQ(helpDesk.getName(), "Help Desk");
    EXPECT_EQ(salesRoom.getType(), "Test");
    EXPECT_EQ(helpDesk.getType(), "Test");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}