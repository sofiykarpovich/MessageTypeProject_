cmake_minimum_required(VERSION 3.16)
project(MessageType LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(MessageTypeLib src/MessageType.cpp)


target_include_directories(MessageTypeLib
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)


if (MSVC)
target_compile_options(MessageTypeLib PRIVATE /W4 /permissive-)
else()
target_compile_options(MessageTypeLib PRIVATE -Wall -Wextra -Wpedantic)
endif()


# --- main ---
add_executable(mainApp src/main.cpp)
target_link_libraries(mainApp PRIVATE MessageTypeLib)


# --- GoogleTest ---
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_MessageType tests/test_MessageType.cpp)
target_link_libraries(test_MessageType PRIVATE MessageTypeLib gtest_main)

include(GoogleTest)
gtest_discover_tests(test_MessageType)
