TEMPLATE = app
TARGET = bhsProductionMeta
QT += testlib

HEADERS += bhsProductionMetaTest.hpp
SOURCES += bhsProductionMetaTest.cpp

INCLUDEPATH += ../include
LIBS += -L../lib -lbhsProductionMeta