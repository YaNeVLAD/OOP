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
    "catch2.h" 
    "test_vector.cpp" 
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.cpp
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.h
    "test_html_decode.cpp"
    ${CMAKE_SOURCE_DIR}/HtmlDecode/HtmlDecode.cpp
    ${CMAKE_SOURCE_DIR}/HtmlDecode/HtmlDecode.h
    "test_generate_prime_numbers_set.cpp"
    ${CMAKE_SOURCE_DIR}/GeneratePrimeNumbersSet/GeneratePrimeNumbersSet.cpp
    ${CMAKE_SOURCE_DIR}/GeneratePrimeNumbersSet/GeneratePrimeNumbersSet.h
)

set_target_properties(catch2 PROPERTIES CXX_STANDARD 20)
target_link_libraries(catch2 PRIVATE Catch2::Catch2)