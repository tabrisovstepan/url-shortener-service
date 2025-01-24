cmake_minimum_required(VERSION 3.20)
project(url_shortener_service)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS OFF)

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(INC_DIR /usr/local/include)
set(LIB_DIR /usr/local/lib)

find_package(Boost 1.81 COMPONENTS program_options json)

list(APPEND INC_DIR ${Boost_INCLUDE_DIRS})
list(APPEND LIB_DIR ${Boost_LIBRARY_DIRS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SQLiteCpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

link_directories(${LIB_DIR})

add_executable(url_shortener_service src/main.cpp
        src/controller/url_shortener_controller.hpp
        src/controller/url_shortener_controller.cpp
        src/service/url_shortener_service.hpp
        src/service/url_shortener_service.cpp)

target_link_libraries(url_shortener_service Boost::program_options Boost::json SQLiteCpp HttpServer)

install(TARGETS url_shortener_service 
        RUNTIME DESTINATION /usr/local/bin)