#-------------------------------------------------
#
# Project created by QtCreator 2013-11-20T09:55:44
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets
QT += quick
TARGET = configurator_app
QMAKE_CXXFLAGS += -fPIC
CONFIG += debug
#TEMPLATE = app
LIBS += ../../../build/Debug/libs/libjlib.so
LIBS += ../configurator_ui/libConfiguratorUI.so
#LIBS += ../../../build/Debug/libs/libconfigurator.a
LIBS += ../../../build/Debug/libs/libconfigurator.so

INCLUDEPATH += ../../system/jlib
INCLUDEPATH += ../../system/include
INCLUDEPATH += ../deploy
INCLUDEPATH += /opt/Qt5.2.1/5.2.1/gcc_64/include/QtCore/5.2.1/QtCore


SOURCES +=\
        MainWindow.cpp \
    Main.cpp \
    MainWindowThread.cpp \
    Worker.cpp

HEADERS  += MainWindow.hpp \
    MainWindowInterface.h \
    MainWindowThread.hpp \
    Worker.hpp

FORMS    += MainWindow.ui

OTHER_FILES += \
    configurator_app.pro.user
