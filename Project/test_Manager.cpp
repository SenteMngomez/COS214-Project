#include <gtest/gtest.h>
#include <sstream>
#include "Manager.h"
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

//MockStaff for testing chain of responsibility
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

class ManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        manager = new Manager("Benson");
        mockPerson = new MockPerson("Finn");
        mockStaffSuccessor = new MockStaff("Skips");
		section = new MockSection("MockSection1");
		mockPerson->addSection(section);
		manager->addSection(section);
        
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        std::cout.rdbuf(originalCoutBuffer);
        delete manager;
        delete mockPerson;
        delete mockStaffSuccessor;
    }
    
    Manager* manager;
    MockPerson* mockPerson;
    MockStaff* mockStaffSuccessor;
	MockSection* section;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(ManagerTest, HandlesHelpRequests) {
	
    mockPerson->sendMessage("Need help", "Help");
    manager->handleRequest(mockPerson);

    
    std::string expectedOutput = "(Manager)Benson will assist Finn with their Help request\n";
    std::string output = outputStream.str();
	EXPECT_EQ(output, expectedOutput);
}

TEST_F(ManagerTest, DelegatesNonHelpRequests) {
    // Set up chain: Manager -> MockStaff
    manager->setSuccessor(mockStaffSuccessor);
    
    mockPerson->sendMessage("Buy plants", "Purchase");
    manager->handleRequest(mockPerson);
    
    // Manager should delegate to successor
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Passing on request to Skips") != std::string::npos);
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
    EXPECT_EQ(mockStaffSuccessor->lastRequestPerson, mockPerson);
}

TEST_F(ManagerTest, DelegatesCareRequests) {
    manager->setSuccessor(mockStaffSuccessor);
    
    std::vector<std::string> plants = {"1", "2"};
    mockPerson->sendMessage("Water plants", "Care", &plants);
    manager->handleRequest(mockPerson);
    
    // Manager should delegate Care requests to successor
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Passing on request to Skips") != std::string::npos);
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
}

TEST_F(ManagerTest, InheritsFromStaff) {
    //Test that Manager properly inherits from Staff
    Staff* staff = manager;
    EXPECT_EQ(staff->getName(), "Benson");
}

TEST_F(ManagerTest, CanSetSuccessor) {
    //Test that Manager can set successor like any Staff
    manager->setSuccessor(mockStaffSuccessor);
    
    //Verify by testing delegation
    mockPerson->sendMessage("Unknown request", "UnknownType");
    manager->handleRequest(mockPerson);
    
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}