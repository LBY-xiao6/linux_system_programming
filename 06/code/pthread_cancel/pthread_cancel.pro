TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

INCLUDEPATH += \
    /home/gec/tools

LIBS += \
    -lpthread
