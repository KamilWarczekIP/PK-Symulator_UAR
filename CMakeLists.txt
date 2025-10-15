cmake_minimum_required(VERSION 3.16)

project(PK-Symulator_UAR LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(PK-Symulator_UAR
  main.cpp
  Testy_UAR.cpp
  ARX.h ARX.cpp
  Klasy.uxf
  RegulatorPID.h RegulatorPID.cpp
  Klasy.qmodel
  mainwindow.ui
  UAR.h UAR.cpp
  Generator.h Generator.cpp
)
target_link_libraries(PK-Symulator_UAR Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS PK-Symulator_UAR
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
