CC = g++

# C++ Compile Option
CXXFLAGS = -Wall -O2

# Linker Option
LDFLAGS = -lncurses

# Source Files Directory
SRC_DIR = ./src

# Object Files Directory
OBJ_DIR = ./obj

# Output
TARGET = Snake

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cpp))

OBJS = $(SRCS:.cpp=.o)

OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

all: $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -MD $(LDFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

-include $(DEPS)