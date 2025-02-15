cmake_minimum_required(VERSION 3.10)
project(exam_simulator LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

file(GLOB TOP_LEVEL_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

file(GLOB_RECURSE SRC_CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(SOURCES ${TOP_LEVEL_CPP} ${SRC_CPP})

include_directories(src/core)
include_directories(src/core/questions)
include_directories(src/shared)

add_executable(exam_simulator ${SOURCES})

target_compile_options(exam_simulator PRIVATE
    -fdiagnostics-color=always
    -g
    -pedantic-errors
    -std=c++2a
    -Wall
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wdisabled-optimization
    -Weffc++
    -Werror
    -Wextra
    -Wformat=2
    -Winit-self
    -Wlogical-op
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wno-unused
    -Wnoexcept
    -Wnull-dereference
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wshadow=local
    -Wsign-conversion
    -Wsign-promo
    -Wstrict-null-sentinel
    -Wstrict-overflow=5
    -Wswitch-default
    -Wundef
    -fprofile-arcs
    -ftest-coverage
    -O0
)

target_link_libraries(exam_simulator PRIVATE
    gcov
    gmock
    gmock_main
    gtest
    gtest_main
    Threads::Threads
)

add_custom_target(test
    COMMAND ./exam_simulator test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS exam_simulator
    COMMENT "🧪 Running unit tests..."
)

add_custom_target(generate_questions
    COMMAND ./exam_simulator generate_questions
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS exam_simulator
    COMMENT "📝 Generating questions..."
)

add_custom_target(check_memory_leaks
    COMMAND valgrind --leak-check=full ./exam_simulator test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS exam_simulator
    COMMENT "🧠 Checking for memory leaks..."
)

add_custom_target(clean_build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "🧹 Removing build directory..."
)

add_custom_target(display_help
    COMMAND echo "Available commands:"
    COMMAND echo "  make test               - Run project in test mode"
    COMMAND echo "  make generate_questions - Generate questions"
    COMMAND echo "  make check_memory_leaks - Check for memory leaks"
    COMMAND echo "  make clean_build       - Remove build directory"
    COMMAND echo "  make display_help        - Show this help"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "📖 Displaying help message..."
)

message(STATUS "CMake configuration complete. Use 'make <target>' where target is one of: test, generate_questions, check_memory_leaks, clean_build, display_help")
