
TEMPLATE = lib
TARGET = qsinhala-t
VERSION = 0.2
DISTFILES += ChangeLog

INCLUDEPATH += .
CONFIG      += qt warn_on debug plugin thread
target.path += $$plugins.path/inputmethods
INSTALLS    += target

# Input

HEADERS += qsinhalainputcontext.h \
           qsinhalainputcontextplugin.h

SOURCES += qsinhalainputcontext.cpp \
           qsinhalainputcontextplugin.cpp

