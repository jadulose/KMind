cmake_minimum_required(VERSION 3.19)

# Configure by yourself
project(KMind VERSION "0.0.1")

# Your config.cmake should contain at least the following properties:
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_PREFIX_PATH "your/cmake/prefix/path")
#set(QT_VERSION 5)
include(config.cmake)

# Debug suffix
set(DEBUG_SUFFIX)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(DEBUG_SUFFIX "d")
endif ()

# Target directory
if (DEBUG_SUFFIX MATCHES "d")
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_DIR}/build/debug)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_DIR}/build/debug)
else()
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_DIR}/build/release)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_DIR}/build/release)
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Required Qt Libraries
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets)

# Find package
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_subdirectory(kmind)

# copy dlls on Windows
include(${PROJECT_DIR}/copy_dlls.cmake)
