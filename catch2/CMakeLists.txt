﻿cmake_minimum_required(VERSION 3.15)

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

    "test_shapes.cpp"
    ${CMAKE_SOURCE_DIR}/Shapes/Circle.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Color.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/LineSegment.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/MockCanvas.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Point.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Rectangle.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Triangle.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Utility.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/BaseShape.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/BaseSolidShape.cpp

    ${CMAKE_SOURCE_DIR}/Shapes/Circle.h
    ${CMAKE_SOURCE_DIR}/Shapes/Color.h
    ${CMAKE_SOURCE_DIR}/Shapes/ICanvas.h
    ${CMAKE_SOURCE_DIR}/Shapes/ICanvasDrawable.h
    ${CMAKE_SOURCE_DIR}/Shapes/BaseShape.h
    ${CMAKE_SOURCE_DIR}/Shapes/BaseSolidShape.h
    ${CMAKE_SOURCE_DIR}/Shapes/LineSegment.h
    ${CMAKE_SOURCE_DIR}/Shapes/MockCanvas.h
    ${CMAKE_SOURCE_DIR}/Shapes/Point.h
    ${CMAKE_SOURCE_DIR}/Shapes/Rectangle.h
    ${CMAKE_SOURCE_DIR}/Shapes/Triangle.h
    ${CMAKE_SOURCE_DIR}/Shapes/Utility.h
    
    "test_date.cpp"
    ${CMAKE_SOURCE_DIR}/Date/Date.cpp
    ${CMAKE_SOURCE_DIR}/Date/Date.h
    
    "test_my_string.cpp"
    ${CMAKE_SOURCE_DIR}/MyVector/ContainerBase.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Iteratable.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Allocator.hpp
    ${CMAKE_SOURCE_DIR}/MyString/String.cpp
    ${CMAKE_SOURCE_DIR}/MyString/String.h
    
    "test_find_max_ex.cpp"
    ${CMAKE_SOURCE_DIR}/FindMaxEx/FindMaxEx.hpp
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

add_executable(test_shapes
    ${CATCH_SOURCES}

    "test_shapes.cpp"

    ${CMAKE_SOURCE_DIR}/Shapes/Circle.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Color.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/LineSegment.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/MockCanvas.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Point.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Rectangle.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Triangle.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/Utility.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/BaseShape.cpp
    ${CMAKE_SOURCE_DIR}/Shapes/BaseSolidShape.cpp

    ${CMAKE_SOURCE_DIR}/Shapes/Circle.h
    ${CMAKE_SOURCE_DIR}/Shapes/Color.h
    ${CMAKE_SOURCE_DIR}/Shapes/ICanvas.h
    ${CMAKE_SOURCE_DIR}/Shapes/ICanvasDrawable.h
    ${CMAKE_SOURCE_DIR}/Shapes/BaseShape.h
    ${CMAKE_SOURCE_DIR}/Shapes/BaseSolidShape.h
    ${CMAKE_SOURCE_DIR}/Shapes/LineSegment.h
    ${CMAKE_SOURCE_DIR}/Shapes/MockCanvas.h
    ${CMAKE_SOURCE_DIR}/Shapes/Point.h
    ${CMAKE_SOURCE_DIR}/Shapes/Rectangle.h
    ${CMAKE_SOURCE_DIR}/Shapes/Triangle.h
    ${CMAKE_SOURCE_DIR}/Shapes/Utility.h
)

add_executable(test_date
    ${CATCH_SOURCES}
    
    "test_date.cpp"
    ${CMAKE_SOURCE_DIR}/Date/Date.cpp
    ${CMAKE_SOURCE_DIR}/Date/Date.h
)

add_executable(test_my_string
    ${CATCH_SOURCES}
    
    "test_my_string.cpp"
    ${CMAKE_SOURCE_DIR}/MyVector/ContainerBase.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Iteratable.hpp
    ${CMAKE_SOURCE_DIR}/MyVector/Allocator.hpp
    ${CMAKE_SOURCE_DIR}/MyString/String.cpp
    ${CMAKE_SOURCE_DIR}/MyString/String.h
)

add_executable(test_http_url
    ${CATCH_SOURCES}
    
    "test_http_url.cpp"
    ${CMAKE_SOURCE_DIR}/ParseUrl/ParseUrl.cpp
    ${CMAKE_SOURCE_DIR}/ParseUrl/ParseUrl.h
    ${CMAKE_SOURCE_DIR}/HttpUrl/Protocol.cpp
    ${CMAKE_SOURCE_DIR}/HttpUrl/Protocol.h
    ${CMAKE_SOURCE_DIR}/HttpUrl/UrlParsingError.hpp
    ${CMAKE_SOURCE_DIR}/HttpUrl/HttpUrl.cpp
    ${CMAKE_SOURCE_DIR}/HttpUrl/HttpUrl.h
)

add_executable(test_string_list
    ${CATCH_SOURCES}
    
    "test_string_list.cpp"
    ${CMAKE_SOURCE_DIR}/MyVector/Iteratable.hpp
    ${CMAKE_SOURCE_DIR}/StringList/List.hpp
    ${CMAKE_SOURCE_DIR}/StringList/ListIterator.hpp
    ${CMAKE_SOURCE_DIR}/StringList/StringList.h
)

add_executable(test_find_max_ex
    ${CATCH_SOURCES}

    "test_find_max_ex.cpp"
    ${CMAKE_SOURCE_DIR}/FindMaxEx/FindMaxEx.hpp
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
test_shapes
test_date
test_my_string
test_http_url
test_string_list
test_find_max_ex
PROPERTIES CXX_STANDARD 20)
target_link_libraries(test_all PRIVATE Catch2::Catch2)
target_link_libraries(test_vector PRIVATE Catch2::Catch2)
target_link_libraries(test_html_decode PRIVATE Catch2::Catch2)
target_link_libraries(test_generate_primes PRIVATE Catch2::Catch2)
target_link_libraries(test_dictionary PRIVATE Catch2::Catch2)
target_link_libraries(test_parse_url PRIVATE Catch2::Catch2)
target_link_libraries(test_car PRIVATE Catch2::Catch2)
target_link_libraries(test_my_vector PRIVATE Catch2::Catch2)
target_link_libraries(test_shapes PRIVATE Catch2::Catch2)
target_link_libraries(test_date PRIVATE Catch2::Catch2)
target_link_libraries(test_my_string PRIVATE Catch2::Catch2)
target_link_libraries(test_http_url PRIVATE Catch2::Catch2)
target_link_libraries(test_string_list PRIVATE Catch2::Catch2)
target_link_libraries(test_find_max_ex PRIVATE Catch2::Catch2)