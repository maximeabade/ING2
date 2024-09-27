# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall

# Source files
SRCS = $(wildcard *.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = exec

# Default target
all: $(EXEC)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	rm -f $(OBJS)

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(EXEC)
