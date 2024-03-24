cmake_minimum_required(VERSION 3.28)
project(TuringMachineEmulator)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/cmake/Qt6")


find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(TuringMachineEmulator
        src/main.cpp
        include/Window.h
        src/Window.cpp
        include/TableWidget.h
        src/TableWidget.cpp
        include/Apparatus.h
        src/Apparatus.cpp

)
target_link_libraries(TuringMachineEmulator PRIVATE Qt6::Widgets)
