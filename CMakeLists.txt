cmake_minimum_required(VERSION 3.9)
project(FlightSimToScraper)

find_package(cpprestsdk CONFIG REQUIRED)

add_executable(FlightSimToScraper src/main.cpp)

target_link_libraries(FlightSimToScraper PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal)

add_executable(TestFlightSimToScraper test/test2.cpp)
