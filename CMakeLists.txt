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
    DisplayStations.cpp
    DisplayHitStreams.cpp
    jsonParser.cpp
    populate.cpp
    network_manager.cpp
    popupImage.cpp
    QMPstatus_error.cpp
    openMedia.cpp
    main.cpp
    mainwindow.cpp
    mousevolume.cpp
    mousevolume.h
    mainwindow.h
    ui_mainwindow.h
    mainwindow.ui
)

target_link_libraries(iHeartRadio Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Multimedia PkgConfig::FFMPEG)

# Set the installation directories to /usr/local/bin
set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install path prefix, prepended onto install directories")

install(TARGETS iHeartRadio
        RUNTIME DESTINATION bin
)

install(FILES ${CMAKE_SOURCE_DIR}/images/iheart-icon.png
        DESTINATION share/icons/hicolor/48x48/apps
)

install(FILES ${CMAKE_SOURCE_DIR}/images/iheart-icon.png
        DESTINATION share/icons/hicolor/48x48/apps
)

install(FILES ${CMAKE_SOURCE_DIR}/iheartradio.desktop
        DESTINATION share/applications
)

# Add the uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)
