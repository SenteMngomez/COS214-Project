#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "GroundStaff.h"
#include "WaterPlant.h"
#include "GIveSunlight.h"
#include "Section.h"
#include "Staff.h"
#include "Person.h"

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

//Mock Person class for testing
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

//Mock Staff for testing chain of responsibility
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

// Mock WaterPlant command
class MockWaterPlant : public WaterPlant {
public:
    MockWaterPlant() : WaterPlant() {}
    
    void execute(vector<std::string>* tags, string decorator = "") override {
        executeCalled = true;
        lastTags = tags;
        lastDecorator = decorator;
        
        //Simulate watering output
        if (tags && !tags->empty()) {
            for (std::string id : *tags) {
                std::cout << "Mock: Plants with the following id has been watered: " << id << std::endl;
            }
        }
    }
    
    bool executeCalled = false;
    vector<std::string>* lastTags = nullptr;
    string lastDecorator = "";
};

//Mock GiveSunlight command
class MockGiveSunlight : public GiveSunlight {
public:
    MockGiveSunlight() : GiveSunlight() {}
    
    void execute(vector<std::string>* tags, string decorator = "") override {
        executeCalled = true;
        lastTags = tags;
        lastDecorator = decorator;
        
        //Simulate giving sunlight output
        if (tags && !tags->empty()) {
            for (std::string id : *tags) {
                std::cout << "Mock: The plant with the following id is being left in the sun for some time : " << id << std::endl;
            }
        }
    }
    
    bool executeCalled = false;
    vector<std::string>* lastTags = nullptr;
    string lastDecorator = "";
};

class GroundStaffTest : public ::testing::Test {
protected:
    void SetUp() override {
        groundStaff = new GroundStaff("Benson");
        mockPerson = new MockPerson("Finn");
        mockStaffSuccessor = new MockStaff("Jake");
        mockWaterPlant = new MockWaterPlant();
        mockGiveSunlight = new MockGiveSunlight();
        mockSection = new MockSection("Greenhouse Area");

		//Seetting up mock sections
		groundStaff->addSection(mockSection);
    	mockSection->addPerson(groundStaff);
    	mockSection->addPerson(mockPerson);
		mockPerson->addSection(mockSection);
        
        //Setting up the commands
        groundStaff->setWaterPlantCommand(mockWaterPlant);
        groundStaff->setGiveSunlightCommand(mockGiveSunlight);
        
        originalCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputStream.rdbuf());
    }
    
    void TearDown() override {
        std::cout.rdbuf(originalCoutBuffer);

    	mockSection->removePerson(groundStaff);
    	mockSection->removePerson(mockPerson);
        
        delete groundStaff;
        delete mockPerson;
        delete mockStaffSuccessor;
        delete mockWaterPlant;
        delete mockGiveSunlight;
        delete mockSection;
    }
    
    GroundStaff* groundStaff;
    MockPerson* mockPerson;
    MockStaff* mockStaffSuccessor;
    MockWaterPlant* mockWaterPlant;
    MockGiveSunlight* mockGiveSunlight;
    MockSection* mockSection;
    std::ostringstream outputStream;
    std::streambuf* originalCoutBuffer;
};

TEST_F(GroundStaffTest, ConstructorSetsName) {
    EXPECT_EQ(groundStaff->getName(), "Benson");
}

TEST_F(GroundStaffTest, HandlesCareRequests) {
    vector<std::string> plants = {"1", "2", "3"};
    mockPerson->sendMessage("Water and care for plants", "Care", &plants);
    
    groundStaff->handleRequest(mockPerson);
    
    std::string output = outputStream.str();
    
    //Should show care assistance message
    EXPECT_TRUE(output.find("(Ground staff)Benson will care for plants: Plant-1, Plant-2, Plant-3\nRequest made by Finn") != std::string::npos);
    
    EXPECT_TRUE(mockWaterPlant->executeCalled);
    EXPECT_TRUE(mockGiveSunlight->executeCalled);
    EXPECT_EQ(mockWaterPlant->lastTags, &plants);
    EXPECT_EQ(mockGiveSunlight->lastTags, &plants);
}

TEST_F(GroundStaffTest, HandlesCareSinglePlant) {
    vector<std::string> plants = {"42"};
    mockPerson->sendMessage("Care for my cactus", "Care", &plants);
    
    groundStaff->handleRequest(mockPerson);
    
    std::string output = outputStream.str();
    
    //Should show care message for single plant
    EXPECT_TRUE(output.find("(Ground staff)Benson will care for plants: Plant-42") != std::string::npos);
    EXPECT_FALSE(output.find(",") != std::string::npos);
    
    EXPECT_TRUE(mockWaterPlant->executeCalled);
    EXPECT_TRUE(mockGiveSunlight->executeCalled);
}

TEST_F(GroundStaffTest, IgnoresEmptyCareRequests) {
    vector<std::string> emptyPlants;
    mockPerson->sendMessage("Care for nothing", "Care", &emptyPlants);
    
    groundStaff->handleRequest(mockPerson);
    
    //Should not call commands for empty requests
    EXPECT_FALSE(mockWaterPlant->executeCalled);
    EXPECT_FALSE(mockGiveSunlight->executeCalled);
    
    
    std::string output = outputStream.str();
    EXPECT_TRUE(output.empty());
}

TEST_F(GroundStaffTest, DelegatesNonCareRequests) {
    groundStaff->setSuccessor(mockStaffSuccessor);
    
    mockPerson->sendMessage("Need help", "Help");
    groundStaff->handleRequest(mockPerson);
    
    //Should delegate to successor
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Passing on request to Jake") != std::string::npos);
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
    EXPECT_EQ(mockStaffSuccessor->lastRequestPerson, mockPerson);
    
    //Should not call care commands
    EXPECT_FALSE(mockWaterPlant->executeCalled);
    EXPECT_FALSE(mockGiveSunlight->executeCalled);
}

TEST_F(GroundStaffTest, DelegatesPurchaseRequests) {
    groundStaff->setSuccessor(mockStaffSuccessor);
    
    vector<std::string> plants = {"1", "2"};
    mockPerson->sendMessage("Buy plants", "Purchase", &plants, "pot");
    groundStaff->handleRequest(mockPerson);
    
    //Should delegate Purchase requests to successor
    std::string output = outputStream.str();
    EXPECT_TRUE(output.find("Passing on request to Jake") != std::string::npos);
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
    
    //Should not call care commands
    EXPECT_FALSE(mockWaterPlant->executeCalled);
    EXPECT_FALSE(mockGiveSunlight->executeCalled);
}

TEST_F(GroundStaffTest, CareForPlantWithBothCommands) {
    vector<std::string> plants = {"5", "10", "15"};
    
    groundStaff->careForPlant(&plants);
    
    // Should execute both commands
    EXPECT_TRUE(mockWaterPlant->executeCalled);
    EXPECT_TRUE(mockGiveSunlight->executeCalled);
    EXPECT_EQ(mockWaterPlant->lastTags, &plants);
    EXPECT_EQ(mockGiveSunlight->lastTags, &plants);
}

TEST_F(GroundStaffTest, CareForPlantWithoutWaterCommand) {
    //Not setting water command
    GroundStaff staffWithoutWater("Skips");
    staffWithoutWater.setGiveSunlightCommand(mockGiveSunlight);
    
    vector<std::string> plants = {"7", "8"};
    staffWithoutWater.careForPlant(&plants);
    
    std::string output = outputStream.str();
    
    //Should show unable to water message
    EXPECT_TRUE(output.find("Skips is unable to water plant(s)") != std::string::npos);
    
    //Should still call sunlight command
    EXPECT_TRUE(mockGiveSunlight->executeCalled);
    EXPECT_EQ(mockGiveSunlight->lastTags, &plants);
}

TEST_F(GroundStaffTest, CareForPlantWithoutSunlightCommand) {
    //Not setting sunlight command
    GroundStaff staffWithoutSunlight("Pops");
    staffWithoutSunlight.setWaterPlantCommand(mockWaterPlant);
    
    vector<std::string> plants = {"9", "10"};
    staffWithoutSunlight.careForPlant(&plants);
    
    std::string output = outputStream.str();
    
    //Should show unable to give sunlight message
    EXPECT_TRUE(output.find("Pops is unable to give sunlight to plant(s)") != std::string::npos);
    
    //Should still call water command
    EXPECT_TRUE(mockWaterPlant->executeCalled);
    EXPECT_EQ(mockWaterPlant->lastTags, &plants);
}

TEST_F(GroundStaffTest, CareForPlantWithoutAnyCommands) {
    GroundStaff staffWithoutCommands("Muscle Man");
    
    vector<std::string> plants = {"11", "12"};
    staffWithoutCommands.careForPlant(&plants);
    
    std::string output = outputStream.str();
    
    //Should show both "Unable to" error messages
    EXPECT_TRUE(output.find("Muscle Man is unable to water plant(s)") != std::string::npos);
    EXPECT_TRUE(output.find("Muscle Man is unable to give sunlight to plant(s)") != std::string::npos);
}

TEST_F(GroundStaffTest, SetWaterPlantCommandWorks) {
    MockWaterPlant* newWaterCommand = new MockWaterPlant();
    groundStaff->setWaterPlantCommand(newWaterCommand);
    
    vector<std::string> plants = {"20", "21"};
    groundStaff->careForPlant(&plants);
    
    //Should use the new command
    EXPECT_TRUE(newWaterCommand->executeCalled);
    EXPECT_FALSE(mockWaterPlant->executeCalled);
    EXPECT_EQ(newWaterCommand->lastTags, &plants);
    
    delete newWaterCommand;
}

TEST_F(GroundStaffTest, SetGiveSunlightCommandWorks) {
    MockGiveSunlight* newSunlightCommand = new MockGiveSunlight();
    groundStaff->setGiveSunlightCommand(newSunlightCommand);
    
    vector<std::string> plants = {"25", "26"};
    groundStaff->careForPlant(&plants);
    
    //Should use the new command
    EXPECT_TRUE(newSunlightCommand->executeCalled);
    EXPECT_FALSE(mockGiveSunlight->executeCalled);
    EXPECT_EQ(newSunlightCommand->lastTags, &plants);
    
    delete newSunlightCommand;
}

TEST_F(GroundStaffTest, FullCareWorkflow) {
    // Set up complete workflow
    
    vector<std::string> plants = {"100", "101", "102"};
    mockPerson->sendMessage("Please care for my plants", "Care", &plants);
    
    groundStaff->handleRequest(mockPerson);
    
    std::string output = outputStream.str();
    
    //Should show care message
    EXPECT_TRUE(output.find("(Ground staff)Benson will care for plants: Plant-100, Plant-101, Plant-102") != std::string::npos);
    EXPECT_TRUE(output.find("Request made by Finn") != std::string::npos);
    
    //Should have executed both commands
    EXPECT_TRUE(mockWaterPlant->executeCalled);
    EXPECT_TRUE(mockGiveSunlight->executeCalled);
    
}

TEST_F(GroundStaffTest, InheritsFromStaff) {
    //Testing that GroundStaff properly inherits from Staff
    Staff* staff = groundStaff;
    EXPECT_EQ(staff->getName(), "Benson");
}

TEST_F(GroundStaffTest, CanSetSuccessor) {
    //Testing that GroundStaff can set successor like any Staff
    groundStaff->setSuccessor(mockStaffSuccessor);
    
    mockPerson->sendMessage("Unknown request", "UnknownType");
    groundStaff->handleRequest(mockPerson);
    
    EXPECT_TRUE(mockStaffSuccessor->handleRequestCalled);
}

//Test with different ground staff names
TEST(GroundStaffBasicTest, DifferentNames) {
    GroundStaff alice("Alice");
    GroundStaff bob("Bob");
    
    EXPECT_EQ(alice.getName(), "Alice");
    EXPECT_EQ(bob.getName(), "Bob");
}

