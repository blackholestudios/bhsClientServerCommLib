TEMPLATE = app
TARGET = bin/bhsProductionMetaTest
QT += testlib

HEADERS += bhsProductionMetaTest.hpp
SOURCES += bhsProductionMetaTest.cpp

INCLUDEPATH += ../include
LIBS += -L../lib -lbhsProductionMeta