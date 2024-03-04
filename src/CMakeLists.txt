cmake_minimum_required(VERSION 3.16)

project(Maze VERSION 1.0.0 LANGUAGES CXX C)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets LinguistTools Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


#set(CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#set(CMAKE_AUTOUIC_SEARCH_PATHS ./UI)
SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT5_DIR}/lib/cmake")
set(CMAKE_AUTOUIC_SEARCH_PATHS ./Views/Ui)
#find_package(OpenGL REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS OpenGL)
#find_package(Qt6  REQUIRED COMPONENTS OpenGLWidgets)
#find_package(Qt6 REQUIRED COMPONENTS Gui)
#set(CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui OpenGL OpenGLWidgets)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
#include_directories("./include/QtGifImage/src/gifimage" "./include/QtGifImage/src/3rdParty/giflib")

#file(GLOB_RECURSE ENGINE_HEADER

file(GLOB PROJECT_SOURCES
        Views/src/MazeSettings/*.cc
        Views/src/MainWindow/*.cc
        Views/src/Draw/*.cc
        Models/src/Parser/*.cc
        Controlers/src/*.cc
        Models/src/EllerAlgo/*.cc
        Models/src/WaveAlgo/*.cc
        Models/src/Recoder/*.cc
        main.cc
        Views/include/MazeSettings/*.h
        Views/include/MainWindow/*.h
        Views/include/Draw/*.h
        Models/include/Parser/*.h
        Models/include/EllerAlgo/*.h
        Models/include/WaveAlgo/*.h
        Models/include/DataStruct/*.h
        Models/include/Recoder/*.h
        Controlers/include/*.h
        Views/Ui/*.ui

        ${TS_FILES}

        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(Maze
                MANUAL_FINALIZATION
                ${PROJECT_SOURCES}
                )

        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
#add_executable(3dViewer ${PROJECT_SOURCES})
endif()

#target_include_directories(3dViewer PRIVATE src)
target_include_directories(Maze PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(Maze PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

#target_link_libraries(3dViewer
#        Qt5::Core
#        Qt5::Gui
#        Qt5::Widgets
#        Qt5::OpenGL
#        Qt5::OpenGLWidgets
#        ${OPENGL_LIBRARIES}
#    )

target_link_libraries(Maze PRIVATE Qt6::OpenGL)
target_link_libraries(Maze PRIVATE Qt6::Gui)
target_link_libraries(Maze PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(Maze PRIVATE Qt6::Core)

# target_link_libraries(${PROJECT_NAME} PRIVATE qtgif)
#set_source_files_properties(ResourceFiles/res.qrc PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")


# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(calc)
# endif()


add_compile_options("-Wall -Wextra -Wpedantic -Werror -mrdrnd")
