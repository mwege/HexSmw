cmake_minimum_required(VERSION 3.21)

project(HexSmw VERSION 0.0.1 LANGUAGES C CXX)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp MainWindow.cpp MainWindow.h HexWidget.cpp HexWidget.h
)
MESSAGE(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

include_directories(
  ${Qt6Core_INCLUDE_DIRS}
  ${Qt6Widgets_INCLUDE_DIRS}
  ${Qt6Qml_INCLUDE_DIRS}
  ${Qt6Quick_INCLUDE_DIRS}
  ${Qt6QuickControls2_INCLUDE_DIRS}
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(capstone CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE capstone::capstone)


target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

