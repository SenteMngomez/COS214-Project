CXX := g++
# Require C++14 for GoogleTest and modern STL features
CXXFLAGS := -g -std=c++14

# Source files (exclude test_*.cpp from the main build)
SRC := $(filter-out test_%.cpp,$(wildcard *.cpp))
TEST_SRC := $(wildcard test_*.cpp)

OBJ := $(SRC:.cpp=.o)

# Exclude test files from main build
MAIN_SRC := $(filter-out test_%.cpp, $(SRC))
MAIN_OBJ := $(MAIN_SRC:.cpp=.o)

TEST_SRC := $(wildcard test_*.cpp)
TEST_OBJ := $(TEST_SRC:.cpp=.o)

TARGET := main
TEST_TARGET := test_runner

all: $(TARGET)

$(TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJ) $(filter-out main.o, $(MAIN_OBJ))
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgtest -lgtest_main -pthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)
	
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET)
