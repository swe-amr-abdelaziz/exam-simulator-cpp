CXX = g++
CXXFLAGS := -fdiagnostics-color=always -g -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -std=c++17
LDFLAGS := -lgtest -lgtest_main -lgmock -lgmock_main -pthread
CCOV := -fprofile-arcs -ftest-coverage -O0

TARGET = build/exam_simulator
SOURCES = $(shell find . -maxdepth 1 -name "*.cpp") $(shell find ./src -type f -name "*.cpp")

.PHONY: all build run test generate_questions check_memory_leaks clean help

all: build

build: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "⏳ Creating build directory..."
	@mkdir -p build
	@echo "⏳ Building project..."
	@$(CXX) $(CXXFLAGS) $(CCOV) $(SOURCES) -o $(TARGET) $(LDFLAGS)
	@echo "✅ Project built successfully!"

run: build
	@./$(TARGET)

test: build
	@./$(TARGET) test

generate_questions: build
	@./$(TARGET) generate_questions

check_memory_leaks: build
	@echo "⏳ Running memory leaks check..."
	@valgrind --leak-check=full ./$(TARGET) test
	@echo "✅ Memory leaks check passed!"

clean:
	@echo "⏳ Removing build directory..."
	@rm -rf build
	@echo "✅ Build directory removed successfully!"

help:
	@echo "Available commands:"
	@echo "  make build              - Build the project executable (only if needed)"
	@echo "  make run                - Run the project normally"
	@echo "  make test               - Run the project in test mode"
	@echo "  make generate_questions - Run the project in generate_questions mode"
	@echo "  make check_memory_leaks - Check for memory leaks in the project"
	@echo "  make clean              - Remove the built executable"
	@echo "  make help               - Show this help message"
