cmake_minimum_required(VERSION 3.5)

project(iHeartRadio LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET libavformat libavcodec libavutil libswscale)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Multimedia)
qt_add_resources(SOURCES resources.qrc)


add_executable(iHeartRadio
    main.cpp
    mainwindow.cpp
    mousevolume.cpp
    mousevolume.h
    mainwindow.h
    ui_mainwindow.h
    mainwindow.ui
)

target_link_libraries(iHeartRadio Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Multimedia PkgConfig::FFMPEG)

