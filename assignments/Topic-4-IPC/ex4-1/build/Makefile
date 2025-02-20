# Compiler
CC = gcc

# Directories
SRC_DIR = ../src
BIN_DIR = ../bin
DATA_DIR = ../data

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Executables (derived from source file names)
EXECUTABLES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SOURCES))

# Build rule
all: create_bin_dir $(EXECUTABLES)

# Create the bin directory if it doesn't exist
create_bin_dir:
	@mkdir -p $(BIN_DIR)
	@echo "Directory '$(BIN_DIR)' created."

# Rule to build each executable
$(BIN_DIR)/%: $(SRC_DIR)/%.c $(DATA_DIR)
	$(CC) $< -o $@
	@echo "Built $@"

# Clean rule
clean:
	rm -rf $(BIN_DIR)
	rm -rf $(DATA_DIR)/output.txt
	@echo "Removed '$(BIN_DIR)' directory and all executables."
