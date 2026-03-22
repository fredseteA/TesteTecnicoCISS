cmake_minimum_required(VERSION 3.15)
project(TesteTecnicoCISS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(api
    src/api.cpp
    src/simian.cpp
)

target_include_directories(api PRIVATE libs src)

if(WIN32)
    target_link_libraries(api PRIVATE ws2_32)
endif()