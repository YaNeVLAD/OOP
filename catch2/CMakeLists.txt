cmake_minimum_required(VERSION 3.15)

project(OOP_Tests)
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(catch2 
    catch2.cpp 
    "test_vector.cpp" 
    "catch2.h" 
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.cpp
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.h
)

set_target_properties(catch2 PROPERTIES CXX_STANDARD 20)
target_link_libraries(catch2 PRIVATE Catch2::Catch2)