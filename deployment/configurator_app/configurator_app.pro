#-------------------------------------------------
#
# Project created by QtCreator 2013-11-20T09:55:44
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = configurator_app
#TEMPLATE = lib
QMAKE_CXXFLAGS += -fPIC
#TEMPLATE = app
LIBS += ../../../build/Debug/libs/libconfigurator.a
LIBS += ../../../build/Debug/libs/libstringlib.so
LIBS += ../../../build/Debug/libs/libjlib.so
LIBS += ../configurator_ui/libConfiguratorUI.so

INCLUDEPATH += ../../system/jlib
INCLUDEPATH += ../../system/include
INCLUDEPATH += ../deploy

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
