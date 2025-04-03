cmake_minimum_required(VERSION 3.15)

project(OOP_Tests)
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.0
)
FetchContent_MakeAvailable(Catch2)

set(CATCH_SOURCES
    catch2.cpp
    catch2.h
)

add_executable(test_all
    ${CATCH_SOURCES}
    "test_vector.cpp"
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.cpp
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.h

    "test_html_decode.cpp"
    ${CMAKE_SOURCE_DIR}/HtmlDecode/HtmlDecode.cpp
    ${CMAKE_SOURCE_DIR}/HtmlDecode/HtmlDecode.h

    "test_generate_primes.cpp"
    ${CMAKE_SOURCE_DIR}/GeneratePrimeNumbers/GeneratePrimeNumbers.cpp
    ${CMAKE_SOURCE_DIR}/GeneratePrimeNumbers/GeneratePrimeNumbers.h

    "test_dictionary.cpp"
    ${CMAKE_SOURCE_DIR}/Dictionary/Dictionary.cpp
    ${CMAKE_SOURCE_DIR}/Dictionary/Dictionary.h

    "test_parse_url.cpp"    
    ${CMAKE_SOURCE_DIR}/ParseUrl/ParseUrl.cpp
    ${CMAKE_SOURCE_DIR}/ParseUrl/ParseUrl.h
    
    "test_car.cpp"
    ${CMAKE_SOURCE_DIR}/Car/CarController.cpp
    ${CMAKE_SOURCE_DIR}/Car/CarController.h
    ${CMAKE_SOURCE_DIR}/Car/Car.cpp
    ${CMAKE_SOURCE_DIR}/Car/Car.h
    
    "test_my_vector.cpp"
    ${CMAKE_SOURCE_DIR}/MyVector/ContainerBase.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Iteratable.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Allocator.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Vector.hpp
)

add_executable(test_vector
    ${CATCH_SOURCES}
    "test_vector.cpp"
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.cpp
    ${CMAKE_SOURCE_DIR}/Vector/VectorProcessor.h
)

add_executable(test_html_decode
    ${CATCH_SOURCES}
    "test_html_decode.cpp"
    ${CMAKE_SOURCE_DIR}/HtmlDecode/HtmlDecode.cpp
    ${CMAKE_SOURCE_DIR}/HtmlDecode/HtmlDecode.h
)

add_executable(test_generate_primes
    ${CATCH_SOURCES}
    "test_generate_primes.cpp"
    ${CMAKE_SOURCE_DIR}/GeneratePrimeNumbers/GeneratePrimeNumbers.cpp
    ${CMAKE_SOURCE_DIR}/GeneratePrimeNumbers/GeneratePrimeNumbers.h
)

add_executable(test_dictionary
    ${CATCH_SOURCES}
    "test_dictionary.cpp"
    ${CMAKE_SOURCE_DIR}/Dictionary/Dictionary.cpp
    ${CMAKE_SOURCE_DIR}/Dictionary/Dictionary.h
)

add_executable(test_parse_url
    ${CATCH_SOURCES}
    "test_parse_url.cpp"    
    ${CMAKE_SOURCE_DIR}/ParseUrl/ParseUrl.cpp
    ${CMAKE_SOURCE_DIR}/ParseUrl/ParseUrl.h
)

add_executable(test_car
    ${CATCH_SOURCES}
    "test_car.cpp"
    
    ${CMAKE_SOURCE_DIR}/Car/CarController.cpp
    ${CMAKE_SOURCE_DIR}/Car/CarController.h
    ${CMAKE_SOURCE_DIR}/Car/Car.cpp
    ${CMAKE_SOURCE_DIR}/Car/Car.h
)

add_executable(test_my_vector
    ${CATCH_SOURCES}
    "test_my_vector.cpp"

    ${CMAKE_SOURCE_DIR}/MyVector/ContainerBase.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Iteratable.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Allocator.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Vector.hpp
)

set_target_properties(
test_all 
test_vector 
test_html_decode
test_generate_primes
test_dictionary
test_parse_url
test_car
test_my_vector
PROPERTIES CXX_STANDARD 20)
target_link_libraries(test_all PRIVATE Catch2::Catch2)
target_link_libraries(test_vector PRIVATE Catch2::Catch2)
target_link_libraries(test_html_decode PRIVATE Catch2::Catch2)
target_link_libraries(test_generate_primes PRIVATE Catch2::Catch2)
target_link_libraries(test_dictionary PRIVATE Catch2::Catch2)
target_link_libraries(test_parse_url PRIVATE Catch2::Catch2)
target_link_libraries(test_car PRIVATE Catch2::Catch2)
target_link_libraries(test_my_vector PRIVATE Catch2::Catch2)