TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

CONFIG += opengl glext
CONFIG += console
LIBS += -lglut -lSDL2 -lSDL2_image -lGLU
INCLUDEPATH += -L/usr/include/
SOURCES += main.cpp \
    graphics.cpp \
    gameobject.cpp \
    gamemath.cpp \
    gamefield.cpp \
    gameplayercontrols.cpp \
    gameplayer.cpp \
    gametimer.cpp \
    gameenemy.cpp \
    gameweapon.cpp

HEADERS += \
    graphics.h \
    gameobject.h \
    gamemath.h \
    gamefield.h \
    gameplayercontrols.h \
    gameplayer.h \
    gameobjecttypes.h \
    gametimer.h \
    gameenemy.h \
    gameweapon.h
