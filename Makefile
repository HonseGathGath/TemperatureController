CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = temp_controller

SRC_DIR = src
DATA_DIR = data
DOCS_DIR = docs

SOURCES = $(SRC_DIR)/main.c \
 	  $(SRC_DIR)/config.c \
 	  $(SRC_DIR)/sensor.c \
    $(SRC_DIR)/decision.c \
	  $(SRC_DIR)/logger.c \
	  $(SRC_DIR)/stats.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(SOURCES) -o $(TARGET)
	@echo "🚀 Build completed: $(TARGET)"

clean:
	rm -f $(TARGET)
	@echo "🧹 Clean completed"

distclean: clean
	@echo "🗑️  Deep clean completed"

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)
	@echo "🐛 Debug build completed"

release: CFLAGS = -Wall -O2 -std=c99
release: $(TARGET)
	@echo "⚡ Release build completed"

test: $(TARGET)
	@echo "✅ Build test passed - ready to run"

tree:
	@echo "📁 Project Structure:"
	@tree -I '*.o|$(TARGET)'

help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run the program"
	@echo "  debug   - Build with debug flags"
	@echo "  release - Build with optimizations"
	@echo "  test    - Test compilation"
	@echo "  tree    - Show project structure"
	@echo "  help    - Show this help"

.PHONY: all clean distclean run debug release test tree help
