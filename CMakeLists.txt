cmake_minimum_required(VERSION 3.19)

project(PK-Symulator_UAR LANGUAGES CXX)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)



set(PROJECT_SOURCES
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
qt_add_executable(PK-Symulator_UAR
  WIN32 MACOSX_BUNDLE
  ${PROJECT_SOURCES}
  #dialogarxnoise.h dialogarxnoise.cpp dialogarxnoise.ui
)
target_link_libraries(PK-Symulator_UAR
    PRIVATE
        Qt::Core
        Qt::Widgets
)
include(GNUInstallDirs)

install(TARGETS PK-Symulator_UAR
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
qt_generate_deploy_app_script(
    TARGET PK-Symulator_UAR
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

#target_link_libraries(PK-Symulator_UAR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#if(${QT_VERSION} VERSION_LESS 6.1.0)
#  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.pksymulatoruar)
#endif()
#set_target_properties(PK-Symulator_UAR PROPERTIES
#    ${BUNDLE_ID_OPTION}
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)


#install(TARGETS PK-Symulator_UAR
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(PK-Symulator_UAR)
#endif()
