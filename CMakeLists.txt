cmake_minimum_required(VERSION 3.1.1)
project(Triad)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(REQUIRED_QT_VERSION 5.7.0)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core Network Quick)

set(triad_src src/main.cpp)
qt5_add_resources(triad_gui gui/qml.qrc)


add_executable(Triad ${triad_src} ${triad_gui})

target_link_libraries(Triad Qt5::Core Qt5::Quick)
