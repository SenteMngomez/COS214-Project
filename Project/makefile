
CXX := g++
CXXFLAGS := -g -std=c++11

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)


TARGET := main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)
	
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
