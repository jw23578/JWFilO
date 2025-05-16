cmake_minimum_required(VERSION 3.16)

project(JWFilO VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Svg)
include_directories("../JWUtils")
include_directories("../JWQTTemplateModel")

set(CMAKE_AUTORCC ON)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appJWFilO
    main.cpp
)

qt_add_qml_module(appJWFilO
    URI JWFilO
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES ../JWQTTemplateModel/jwqtobjectinterface.h  ../JWQTTemplateModel/jwqtidobjectinterface.cpp ../JWQTTemplateModel/jwqt_macros.h ../JWQTTemplateModel/jwqttemplatemodelinterface.h ../JWQTTemplateModel/jwqtobjectinterface.cpp ../JWQTTemplateModel/jwqttemplatemodel.h ../JWQTTemplateModel/jwqtmodelinterface.cpp ../JWQTTemplateModel/jwqtidobjectinterface.h  ../JWQTTemplateModel/indexedpointercontainer.h  ../JWQTTemplateModel/jwqtmodelinterface.h
        SOURCES filoconfig.h filoconfig.cpp
        SOURCES filo.h filo.cpp
        SOURCES typeobject.h typeobject.cpp
        SOURCES suffixobject.h suffixobject.cpp
        SOURCES fileobject.h fileobject.cpp
        SOURCES fileloadworker.h fileloadworker.cpp
        RESOURCES notepad.txt
        RESOURCES
        RESOURCES images.qrc
        QML_FILES qmlElements/FILOText.qml
        QML_FILES qmlElements/FILOSquareImageButton.qml
        SOURCES colors.h colors.cpp
        QML_FILES qmlElements/GroupRectangle.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appJWFilO PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appJWFilO
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appJWFilO
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appJWFilO
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
