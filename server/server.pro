TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../event.cpp \
        ../utilities.cpp \
        eventhandler.cpp \
        game/game.cpp \
        main.cpp \
        server.cpp

HEADERS += \
    ../event.h \
    ../utilities.h \
    eventhandler.h \
    game/game.h \
    server.h

DISTFILES += \
    ../dataStructure.txt

LIBS += -lws2_32
