cmake_minimum_required(VERSION 3.5)

project(music_match VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Sqlite3 REQUIRED)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 871ed52d350214a034f6ef8a3b8f51c5ce1bd400) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        database.cpp
        database.h
        second_page.cpp
        second_page.h
        second_page.ui
        calling_api.cpp
        calling_api.h
        third_page.cpp
        third_page.h
        third_page.ui
        fourth_page.cpp
        fourth_page.h
        fourth_page.ui
        last_page.cpp
        last_page.h
        last_page.ui
        genres.cpp
        genres.h
        tokenize_parse.cpp
        tokenize_parse.h
        get_artistid.cpp
        get_artistid.h
        get_audiofeatures.cpp
        get_audiofeatures.h
        get_trackid.cpp
        get_trackid.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(music_match
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET music_match APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(music_match SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(music_match
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(music_match PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(music_match PRIVATE cpr::cpr)

find_package (SQLite3)

include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (music_match PRIVATE ${SQLite3_LIBRARIES})

set_target_properties(music_match PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS music_match
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(music_match)
endif()
