TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../event.cpp \
        ../utilities.cpp \
        eventhandler.cpp \
        main.cpp \
        server.cpp \
        thread_example.cpp

HEADERS += \
    ../event.h \
    ../utilities.h \
    eventhandler.h \
    server.h

DISTFILES += \
    ../dataStructure.txt
