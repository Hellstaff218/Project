CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
TARGET = app
BUILD_DIR = build
SOURCES = main.cpp \
	sorts.cpp \
	HW1.cpp \
	gnuplot.cpp \
	research_cond.cpp
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
