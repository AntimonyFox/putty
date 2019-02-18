# the compiler: gcc for C program, define as g++ for C++
CC = g++

SRC_DIR := src
OBJ_DIR := obj
BUILD_DIR = build
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# Alt for patsubst: $(var:pattern=replacement)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
# Linker flags (linker is ld)
LDFLAGS := -lws2_32
# compiler flags: -g: debugging, -Wall: turn on compiler warnings
CPPFLAGS := -g -Wall -std=c++11 -Iinclude
# CXXFLAGS := ...

# ???
# CXXFLAGS += -MMD
# -include $(OBJ_FILES:.o=.d)



# MKDIR_P = mkdir -p

# .PHONY: directories

# directories: ${OUT_DIR}

# ${OUT_DIR}:
#         ${MKDIR_P} ${OUT_DIR}

# the build target executable:
TARGET = $(BUILD_DIR)/putty

# When you specify a target after the colon, it will build those targets, 
# and then run the indented procedure for this build target
all: directories $(TARGET)

# Ensure necessary directories exist
directories:
	@mkdir -p obj
	@mkdir -p build

# I guess g++ -o output %.o simply links everything together?
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS) 
	# $(CC) $(CPPFLAGS) -o $@ -Iinclude src/main.cpp

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(TARGET)
	rm -r obj
