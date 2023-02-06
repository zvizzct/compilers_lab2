# Executable file name
EXE = preprocesor

# Source file name
SRC = preprocesor.c

# Header file name
INC = src/utilsFiles.h

# Compilation command
CC = gcc

# Compilation options
CFLAGS = -g

# Rule to build the executable
$(EXE): $(SRC) $(INC)
	$(CC) $(SRC) $(INC) $(CFLAGS) -o $(EXE)

# Rule to clean up the executable generated during compilation
clean:
	rm -f $(EXE)

.PHONY: clean

# Default rule
all: clean $(EXE)