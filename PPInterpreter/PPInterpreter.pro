TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    lexer.cpp \
    parser.cpp

HEADERS += \
    lexer.h \
    ast.h \
    token.h \
    parser.h \
    programContext.h \
    visitor.h

