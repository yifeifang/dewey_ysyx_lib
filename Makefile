# Define the compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O0 -g
PREFIX = /usr/local
INC_DIR = include

# Define the source files and object files
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Define the output library name
LIB = dewey_ysyx.a

# Define the rule to make the library
$(LIB): $(OBJ)
	ar rcs $@ $^

# Define the rule to make the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I include

install: $(LIB)
	cp $(INC_DIR)/dewey_ysyx.h $(PREFIX)/include

# Define the rule to clean the files
clean:
	rm -f $(OBJ) $(LIB)
