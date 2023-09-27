# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Source files
SOURCES = USocial.cpp User.cpp Post.cpp Message.cpp Media.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXEC = usocial_app

# Compile and link the program
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
