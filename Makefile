CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = Main.cpp \
	UserInterface.cpp \
	Solver.cpp \
	Tetromino.cpp \
	PuzzleField.cpp

OBJ = $(SRC:.cpp=.o)
DEPS = UserInterface.h Solver.h Tetromino.h PuzzleField.h

TARGET = kursuch

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)