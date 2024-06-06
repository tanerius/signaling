cmake_minimum_required(VERSION 3.14)

project(Signaling 
    VERSION			1.0.0
    DESCRIPTION		"Signaling library"
    LANGUAGES		CXX	C
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library
add_library(Signaling INTERFACE)
target_include_directories(Signaling INTERFACE include/)

# Google Test setup

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the test executable
add_executable(runTests tests/test_Signaling.cpp)
target_link_libraries(runTests GTest::gtest_main Signaling)
add_test(NAME runTests COMMAND runTests)
