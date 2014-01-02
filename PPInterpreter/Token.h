#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using std::string;

struct Token{
    enum Type{
        LP, RP, COL, COM,
        ASGN, EQ, NE, GE, LE, GT, LT,
        PLUS, MINUS, MULT, DIV,
        DEF, RET, END, WHILE, IF, PRINT, READ,
        VAR, NUM,
        CR, WTF, Eof
    };

    Type type;
    int value;
    string name;

    Token(Type t = WTF, int val = 0, string const &name = ""):
        type(t),
        value(val),
        name(name)
    {}
};

#endif // TOKEN_H
