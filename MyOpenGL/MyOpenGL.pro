#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:11:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app
LIBS += -lopengl32

SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    sphere.cpp \
    orbit.cpp \
    satellite.cpp \
    radar.cpp

HEADERS  += window.h \
    myglwidget.h \
    sphere.h \
    orbit.h \
    satellite.h \
    sceneobjects.h \
    radar.h

FORMS    += window.ui
