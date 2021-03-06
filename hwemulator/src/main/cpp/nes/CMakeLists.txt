cmake_minimum_required(VERSION 3.4.1)
project(hwemulator_nes)

include_directories(
        #        ${CMAKE_SOURCE_DIR}/src/main/cpp/sdl2/include
        #        ${CMAKE_SOURCE_DIR}/src/main/cpp/sdl1x/include
        ${CMAKE_SOURCE_DIR}/src/main/cpp/common/include
        ${CMAKE_SOURCE_DIR}/src/main/cpp/nes/infones
        ${CMAKE_SOURCE_DIR}/src/main/cpp/hwemulatorbase/include
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
endif ()

file(
        GLOB
        SOURCES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/infones/*.cpp
        ${PROJECT_SOURCE_DIR}/infones/android/*.cpp
#        ${PROJECT_SOURCE_DIR}/infones/mapper/*.cpp
)
add_library(
        hwemulator_nes
        SHARED
        ${SOURCES}
)

find_library(
        log-lib
        log)

target_link_libraries(
        hwemulator_nes
        hwemulatorbase
        android
        ${log-lib}
)