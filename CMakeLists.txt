cmake_minimum_required(VERSION 3.9)
project(FlightSimToScraper)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Taco/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(cpprestsdk CONFIG REQUIRED)


set(CMAKE_C_COMPILER "cl")
set(CMAKE_CXX_COMPILER "cl")

add_executable(FlightSimToScraper src/main.cpp)


target_link_libraries(FlightSimToScraper PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal)