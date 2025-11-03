#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Person.h"
#include "Section.h"

// Mock Section class for testing
class MockSalesSection : public Section {
public:
    MockSalesSection(std::string name) : Section(name) {
		type="Sales";
	}
    
    void notify(Person* person) override {
        notifyCalled = true;
        lastNotifiedPerson = person;
        notifyCallCount++;
    }
    
    bool notifyCalled = false;
    Person* lastNotifiedPerson = nullptr;
    int notifyCallCount = 0;
};

class MockHelpSection : public Section {
public:
    MockHelpSection(std::string name) : Section(name) {
		type="Help";
	}
    
    void notify(Person* person) override {
        notifyCalled = true;
        lastNotifiedPerson = person;
        notifyCallCount++;
    }
    
    bool notifyCalled = false;
    Person* lastNotifiedPerson = nullptr;
    int notifyCallCount = 0;
};

//Concrete Person implementation for testing
class TestPerson : public Person {
public:
    TestPerson(std::string name) : Person(name) {}
    
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

class PersonTest : public ::testing::Test {
protected:
    void SetUp() override {
        person = new TestPerson("Finn");
        otherPerson = new TestPerson("Jake");
        mockSection1 = new MockHelpSection("Help Desk");
        mockSection2 = new MockSalesSection("Sales Room");
        
        // Redirect cout to capture output
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(originalCoutBuffer);
        
        delete person;
        delete otherPerson;
        delete mockSection1;
        delete mockSection2;
    }
    
    TestPerson* person;
    TestPerson* otherPerson;
    MockHelpSection* mockSection1;
    MockSalesSection* mockSection2;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(PersonTest, ConstructorSetsName) {
    EXPECT_EQ(person->getName(), "Finn");
    EXPECT_EQ(otherPerson->getName(), "Jake");
}

TEST_F(PersonTest, ConstructorInitializesAttributes) {
    //Check that attributes are properly initialized
    EXPECT_EQ(person->getMessageType(), "");
    EXPECT_EQ(person->getMessage(), "");
    EXPECT_EQ(person->getDecorator(), "");
    EXPECT_EQ(person->getTags(), nullptr);
}

TEST_F(PersonTest, SendMessageWithoutSections) {
    
    person->sendMessage("Hello", "Help");
    
    //Should output error message
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("####Finn is not in any room ####") != std::string::npos);
}

TEST_F(PersonTest, AddSectionWorks) {
    person->addSection(mockSection1);
    
    person->sendMessage("Test message", "Help");
    
    //Should not show error message
    std::string output = outputStream.str();
    EXPECT_FALSE(output.find("####Finn is not in any room ####") != std::string::npos);
    
    //Section should be notified
    EXPECT_TRUE(mockSection1->notifyCalled);
    EXPECT_EQ(mockSection1->lastNotifiedPerson, person);
}

TEST_F(PersonTest, SendMessageWithSingleSection) {
    person->addSection(mockSection1);
    
    std::vector<std::string> tags = {"1", "2", "3"};
    person->sendMessage("Help me", "Help", &tags);
    
    //Check message attributes are set correctly
    EXPECT_EQ(person->getMessage(), "Help me");
    EXPECT_EQ(person->getMessageType(), "Help");
    EXPECT_EQ(person->getTags(), &tags);
    
    //Section should be notified
    EXPECT_TRUE(mockSection1->notifyCalled);
    EXPECT_EQ(mockSection1->lastNotifiedPerson, person);
}

TEST_F(PersonTest, SendMessageWithTwoSectionsNonPurchase) {
    person->addSection(mockSection1); 
    person->addSection(mockSection2);
    
    //Send non-Purchase message
    person->sendMessage("Need help", "Help");
    
    //First section should be notified
    EXPECT_TRUE(mockSection1->notifyCalled);
    EXPECT_EQ(mockSection1->lastNotifiedPerson, person);
    
    //Second section should NOT be notified
    EXPECT_FALSE(mockSection2->notifyCalled);
}

TEST_F(PersonTest, SendMessageWithTwoSectionsPurchase) {
    person->addSection(mockSection1);
    person->addSection(mockSection2); 
    
    //Send Purchase message - should use second section
    std::vector<std::string> tags = {"5", "6"};
    person->sendMessage("Buy plants", "Purchase", &tags, "pot");
    
    EXPECT_TRUE(mockSection2->notifyCalled);
    EXPECT_EQ(mockSection2->lastNotifiedPerson, person);
    
    //First section should NOT be notified
    EXPECT_FALSE(mockSection1->notifyCalled);
}

TEST_F(PersonTest, SendMessageWithTwoSectionsPurchaseComplete) {
    person->addSection(mockSection1);
    person->addSection(mockSection2); 
    
    // Send Purchase Complete message - should use second section
    person->sendMessage("Purchase finished", "Purchase Complete");
    
    //Second section should be notified
    EXPECT_TRUE(mockSection2->notifyCalled);
    EXPECT_EQ(mockSection2->lastNotifiedPerson, person);
    
    //First section should NOT be notified
    EXPECT_FALSE(mockSection1->notifyCalled);
}

TEST_F(PersonTest, SendMessageWithOptionalParameters) {
    person->addSection(mockSection1);
    
    //Send message with default parameters
    person->sendMessage("Simple message", "Help");
    
    EXPECT_EQ(person->getMessage(), "Simple message");
    EXPECT_EQ(person->getMessageType(), "Help");
    EXPECT_EQ(person->getTags(), nullptr);
    EXPECT_EQ(person->getDecorator(), "");
}

TEST_F(PersonTest, SendMessageWithAllParameters) {
    person->addSection(mockSection1);
    
    std::vector<std::string> tags = {"10", "20", "30"};
    person->sendMessage("Complex message", "Care", &tags, "special");
    
    EXPECT_EQ(person->getMessage(), "Complex message");
    EXPECT_EQ(person->getMessageType(), "Care");
    EXPECT_EQ(person->getTags(), &tags);
    EXPECT_EQ(person->getDecorator(), "special");
}

TEST_F(PersonTest, MessageAttributesOverwritten) {
    person->addSection(mockSection1);
    
    //Send first message
    std::vector<std::string> tags1 = {"1", "2"};
    person->sendMessage("First message", "Help", &tags1, "first");
    
    EXPECT_EQ(person->getMessage(), "First message");
    EXPECT_EQ(person->getMessageType(), "Help");
    EXPECT_EQ(person->getTags(), &tags1);
    EXPECT_EQ(person->getDecorator(), "first");
    
    //Send second message - should overwrite
    std::vector<std::string> tags2 = {"3", "4", "5"};
    person->sendMessage("Second message", "Purchase", &tags2, "second");
    
    EXPECT_EQ(person->getMessage(), "Second message");
    EXPECT_EQ(person->getMessageType(), "Purchase");
    EXPECT_EQ(person->getTags(), &tags2);
    EXPECT_EQ(person->getDecorator(), "second");
}

TEST_F(PersonTest, ReceiveMessageIsVirtual) {

    Person* basePerson = person;
    
    otherPerson->addSection(mockSection1);
    otherPerson->sendMessage("Test", "Help");
    
    basePerson->receiveMessage(otherPerson, mockSection1);
    
    //Should call the derived implementation
    EXPECT_EQ(person->lastSender, otherPerson);
    EXPECT_EQ(person->lastSection, mockSection1);
    EXPECT_EQ(person->receivedMessages.size(), 1);
}

TEST_F(PersonTest, GettersReturnCorrectValues) {
    person->addSection(mockSection1);
    
    std::vector<std::string> tags = {"100", "200"};
    person->sendMessage("Getter test", "Test Type", &tags, "test decorator");
    
    //Test all getters
    EXPECT_EQ(person->getName(), "Finn");
    EXPECT_EQ(person->getMessage(), "Getter test");
    EXPECT_EQ(person->getMessageType(), "Test Type");
    EXPECT_EQ(person->getTags(), &tags);
    EXPECT_EQ(person->getDecorator(), "test decorator");
}

TEST_F(PersonTest, AddMultipleSectionsSpecify) {
    MockHelpSection* section3 = new MockHelpSection("Third Room");
    
    person->addSection(mockSection1);
    person->addSection(mockSection2);
    person->addSection(section3);
    
    person->sendMessage("Multi-section test", "Help",nullptr,"","Third Room");
    
    EXPECT_FALSE(mockSection1->notifyCalled);
    EXPECT_FALSE(mockSection2->notifyCalled);
    EXPECT_TRUE(section3->notifyCalled);
    
    delete section3;
}

TEST_F(PersonTest, EmptyTagsVector) {
    person->addSection(mockSection1);
    
    std::vector<std::string> emptyTags;
    person->sendMessage("Empty tags test", "Care", &emptyTags);
    
    EXPECT_EQ(person->getTags(), &emptyTags);
    EXPECT_TRUE(person->getTags()->empty());
}

TEST_F(PersonTest, NullTagsPointer) {
    person->addSection(mockSection1);
    
    person->sendMessage("Null tags test", "Help", nullptr);
    
    EXPECT_EQ(person->getTags(), nullptr);
}

//Test with different person names
TEST(PersonBasicTest, DifferentNames) {
    TestPerson alice("Alice");
    TestPerson bob("Bob");
    
    EXPECT_EQ(alice.getName(), "Alice");
    EXPECT_EQ(bob.getName(), "Bob");
}

