# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Define the target executable
TARGET = main

# List of source files
SRCS = main.cpp ReadCSV.cpp A_Star.cpp Dijkstras.cpp

# Object files (each .cpp file gets compiled to a corresponding .o file)
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build each object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
