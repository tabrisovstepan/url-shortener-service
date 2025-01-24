cmake_minimum_required(VERSION 3.20)
project(HttpServer VERSION 1.0 
                   DESCRIPTION "Http server library"
                   LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.81 COMPONENTS json)

aux_source_directory(src SOURCES)

add_library(HttpServer SHARED ${SOURCES})

target_link_libraries(HttpServer Boost::json)
target_include_directories(HttpServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)