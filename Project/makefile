
CXX := g++
# Require C++14 for GoogleTest and modern STL features
CXXFLAGS := -g -std=c++14

# Source files (exclude test_*.cpp from the main build)
SRC := $(filter-out test_%.cpp,$(wildcard *.cpp))
TEST_SRC := $(wildcard test_*.cpp)

OBJ := $(SRC:.cpp=.o)
TEST_OBJ := $(TEST_SRC:.cpp=.o)

TARGET := main
TEST_TARGET := runTests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test runner target: links test objects with GoogleTest
# Exclude main.o so gtest's main() is used as the program entrypoint
$(TEST_TARGET): $(OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(filter-out main.o,$(OBJ)) $(TEST_OBJ) -lgtest -lgtest_main -pthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)
	
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)
