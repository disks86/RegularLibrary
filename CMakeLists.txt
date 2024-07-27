cmake_minimum_required(VERSION 3.0)
project(RegularLibrary)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/System)
include_directories(${CMAKE_SOURCE_DIR}/Core)
include_directories(${CMAKE_SOURCE_DIR})

if(APPLE)
    file(GLOB_RECURSE PLATFORM_CPP_FILES "${CMAKE_SOURCE_DIR}/*.MacOS.cpp")
    file(GLOB_RECURSE PLATFORM_H_FILES "${CMAKE_SOURCE_DIR}/*.MacOS.h")
endif()

if(WIN32)
    file(GLOB_RECURSE PLATFORM_CPP_FILES "${CMAKE_SOURCE_DIR}/*.Windows.cpp")
    file(GLOB_RECURSE PLATFORM_H_FILES "${CMAKE_SOURCE_DIR}/*.Windows.h")
endif()

if(UNIX AND NOT APPLE)
    file(GLOB_RECURSE PLATFORM_CPP_FILES "${CMAKE_SOURCE_DIR}/*.Linux.cpp")
    file(GLOB_RECURSE PLATFORM_H_FILES "${CMAKE_SOURCE_DIR}/*.Linux.h")
endif()

message(STATUS "Found CPP files: ${ALL_CPP_FILES}")
message(STATUS "Found H files: ${ALL_H_FILES}")

add_library(${PROJECT_NAME} SHARED ${PLATFORM_CPP_FILES} ${PLATFORM_H_FILES}
        Export.h
        System/Allocator.h
        RegularLibrary.h
        RegularLibrary.cpp
        Core/Expected.h
        System/Console.h
        Core/List.cpp
        Core/List.h
        Core/AsciiString.cpp
        Core/AsciiString.h
        Core/Math.cpp
        Core/Math.h
        Core/Expected.cpp
        Core/MemoryConsumer.cpp
        Core/MemoryConsumer.h
        Core/UnicodeString.cpp
        Core/UnicodeString.h
        Core/Pair.cpp
        Core/Pair.h)

target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_REGULARLIBRARY)

# Platform-specific settings
if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)

    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${COCOA_LIBRARY}
            ${OPENGL_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREFOUNDATION_LIBRARY}
    )
endif()

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
    target_link_libraries(${PROJECT_NAME} PRIVATE user32 kernel32 gdi32)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()
