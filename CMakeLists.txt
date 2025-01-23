cmake_minimum_required(VERSION 3.20)
project(url_shortener_service)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost 1.81 COMPONENTS program_options json)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/SQLiteCpp)

add_executable(url_shortener_service src/main.cpp
        src/lib/http_server.hpp
        src/lib/http_server.cpp
        src/lib/abstract_controller.hpp
        src/lib/abstract_controller.cpp
        src/controller/url_shortener_controller.hpp
        src/controller/url_shortener_controller.cpp
        src/service/url_shortener_service.hpp
        src/service/url_shortener_service.cpp
        src/lib/utils.hpp)

target_link_libraries(url_shortener_service Boost::program_options Boost::json SQLiteCpp)