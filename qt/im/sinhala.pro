TEMPLATE = lib
TARGET = qsinhala-t
DESTDIR  = ../../../inputmethods

INCLUDEPATH += .
CONFIG      += qt warn_on debug plugin
target.path += $$plugins.path/inputmethods
INSTALLS    += target

# Input
HEADERS += qsinhalainputcontext.h \
           qsinhalainputcontextplugin.h
SOURCES += qsinhalainputcontext.cpp \
           qsinhalainputcontextplugin.cpp
