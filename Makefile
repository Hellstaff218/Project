CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
TARGET = app
SOURCES = main.cpp sorts.cpp HW1.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
