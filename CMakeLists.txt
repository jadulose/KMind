cmake_minimum_required(VERSION 3.21)

# Configure by yourself
project(KMind)

# Your config.cmake should contain at least the following properties:
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_PREFIX_PATH "~/package/Qt/6.0.3/gcc_64/lib/cmake")
#set(QT_VERSION 6)
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

# Project sources
set(PROJECT_SOURCES
        kmind.cpp
        gui/kmMainWindow.cpp gui/kmMainWindow.ui
        core/kmNode.cpp painter/style.cpp painter/painter.cpp
        gui/kmPaintWidget.cpp painter/styleUtil.cpp painter/formwork.cpp
        gui/kmMainWindow.h core/kmNode.h painter/style.h painter/painter.h
        gui/kmPaintWidget.h painter/styleUtil.h painter/formwork.h
        core/kmNodeType.h
        )

if (NOT DEBUG_SUFFIX MATCHES "d")
    set(PROJECT_SOURCES WIN32 ${PROJECT_SOURCES})
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Find package & link
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

# copy dlls on Windows
include(${PROJECT_DIR}/copy_dlls.cmake)
