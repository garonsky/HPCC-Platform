TEMPLATE =lib
QT += qml quick
QMAKE_CXXFLAGS += -fPIC
CONFIG += debug
CONFIG += dll
CONFIG += plugin
HEADERS += ConfiguratorUI.hpp
HEADERS += AppData.hpp
SOURCES += ConfiguratorUI.cpp AppData.cpp
INCLUDEPATH += ../configurator
INCLUDEPATH += ../../system/jlib
INCLUDEPATH += ../../system/include
INCLUDEPATH += ../deploy
TARGET = ConfiguratorUI