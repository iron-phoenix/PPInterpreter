TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    lexer.cpp

HEADERS += \
    lexer.h \
    ast.h \
    token.h

