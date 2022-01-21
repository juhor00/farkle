QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../event.cpp \
    ../utilities.cpp \
    ./gui/dice.cpp \
    client.cpp \
    eventhandler.cpp \
    main.cpp \
    ./gui/mainwindow.cpp

HEADERS += \
    ../event.h \
    ../utilities.h \
    ./gui/dice.h \
    client.h \
    eventhandler.h \
    ./gui/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../dataStructure.txt \
    networkConfig.txt

FORMS += \
    ./gui/mainwindow.ui

LIBS += -lws2_32

RESOURCES += \
    ./gui/Resources.qrc
