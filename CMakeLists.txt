# set minimum cmake version
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# project name and language
project(Task1 VERSION 0.1 LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
 # SOURCE_DIR "<path_to>/googletest-main"
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(Task1 main.cpp CircularBuffer.cpp)

add_executable(Task1_tests CircularBuffer.cpp CircularBufferTest.cpp)
target_link_libraries(Task1_tests PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(Task1_tests)
