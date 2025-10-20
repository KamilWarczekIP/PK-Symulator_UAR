cmake_minimum_required(VERSION 3.16)

project(PK-Symulator_UAR LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


add_executable(PK-Symulator_UAR
  main.cpp
  Testy_UAR.cpp
  ARX.h ARX.cpp
  RegulatorPID.h RegulatorPID.cpp
  UAR.h UAR.cpp
  Generator.h Generator.cpp
  GeneratorSinusoida.h GeneratorSinusoida.cpp
  GeneratorProstokatny.h GeneratorProstokatny.cpp
  State.h State.cpp
  Test.h Test.cpp
  dialogarxcooeficients.ui mainwindow.ui
)

include(GNUInstallDirs)
install(TARGETS PK-Symulator_UAR
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
