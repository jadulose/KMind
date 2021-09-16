# Project sources
set(PROJECT_SOURCES
        kmind.cpp
        kmMainWindow.cpp kmMainWindow.ui kmMainWindow.h
        kmNode.cpp style.cpp
        kmPaintWidget.cpp styleUtil.cpp formwork.cpp
        kmPaintWidget.h kmNode.h style.h
        styleUtil.h formwork.h
        kmNodeType.h
        kmnodeedit.h kmnodeedit.cpp
        )

include_directories(.)

if (NOT DEBUG_SUFFIX MATCHES "d")
    set(PROJECT_SOURCES WIN32 ${PROJECT_SOURCES})
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
