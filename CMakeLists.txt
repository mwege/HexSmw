cmake_minimum_required(VERSION 3.21)

project(HexSmw VERSION 0.0.1 LANGUAGES C CXX)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (LINUX)
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=readability-*,performance-*,modernize-*,misc-*,google-*,cppcore-guidelines-*,bugbrone-*")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
    set(VCPKG_TARGET_TRIPLET "x64-linux-clang" CACHE STRING "")
  endif()

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/main.cpp 
    src/MainWindow.cpp 
    src/MainWindow.h 
    src/Widgets/EditorStackWidget.cpp 
    src/Widgets/EditorStackWidget.h
    src/Widgets/AsmEditorWidget.cpp
    src/Widgets/AsmEditorWidget.h
    src/Widgets/HexEditorWidget.cpp
    src/Widgets/HexEditorWidget.h
    src/Widgets/ToolbarWidget.h
    src/Widgets/ToolbarWidget.cpp
)
MESSAGE(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

include_directories(
  ${Qt6Core_INCLUDE_DIRS}
  ${Qt6Widgets_INCLUDE_DIRS}
  ${Qt6Qml_INCLUDE_DIRS}
  ${Qt6Quick_INCLUDE_DIRS}
  ${Qt6QuickControls2_INCLUDE_DIRS}
  src
  src/Widgets
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(capstone CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE capstone::capstone)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

