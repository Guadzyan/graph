cmake_minimum_required(VERSION 3.2)
project(graph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(graph main.cpp src/model/player.h  src/headers/libs.h server/hdr/TcpServer.h server/src/TcpServer.cpp server/hdr/TcpClient.h server/src/TcpClient.cpp)
include_directories(graph cmake-build-debug/fonts)
include_directories(graph cmake-build-debug/images)
include_directories(graph libs)
include_directories(graph)
FILE(COPY images DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY fonts DESTINATION "${CMAKE_BINARY_DIR}")


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(graph ${SFML_LIBRARIES})
endif()