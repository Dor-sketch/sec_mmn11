# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c++14

# Linker flags
LDFLAGS = -lfmt

# Source files
SOURCES = USocial.cpp User.cpp Post.cpp Message.cpp Media.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXEC = usocial_app

# Compile and link the program
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
