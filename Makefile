CXX = g++
# Using minimal flags for a bare-metal feel
CXXFLAGS = -Wall -Wextra -g -std=c++11 -fno-exceptions -fno-rtti

TARGET = bibmanager

SOURCES = main.cpp Publication.cpp PublicationList.cpp Syscalls.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default rule: build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Generic rule for compiling .cpp files
# This depends on the .cpp file and any .h file with the same base name
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Specific dependencies for objects that include other headers
main.o: main.cpp PublicationList.h Syscalls.h
PublicationList.o: PublicationList.cpp Publication.h
Publication.o: Publication.cpp Syscalls.h

# Clean rule: remove generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean