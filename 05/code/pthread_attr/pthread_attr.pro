TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

LIBS += \
    -lpthread #链接线程库

INCLUDEPATH += \
    /home/gec/tools
