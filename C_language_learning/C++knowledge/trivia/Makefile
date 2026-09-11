CXX = g++
CXXFLAG = -Wall -Wextra -std=c++17 -pedantic -I

TARGET = test

SRC = test.cpp constant.cpp

OBJ = $(patsubst %.cpp, %.o, $(SRC))

%.o : %.cpp
	$(CXX) $(CXXFLAG) -MMD -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

all: $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) *.d

-include $(patsubst %.o, %.d, $(OBJ))