#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include "Token.h"

using std::string;
using std::istream;

struct Lexer{
    istream &sourceStream;
    size_t currentLine;

public:
    Lexer(istream &sourceStream):
        sourceStream(sourceStream),
        currentLine(1)
    {}

    Token nextToken();
    bool checkToken(Token::Type t, size_t steps = 1);

    size_t getLineNumber() const{
        return currentLine;
    }

private:
    Token getIdentifier();
    Token getNumber();
    Token getSymbol();

    Lexer(Lexer const &);
    Lexer &operator=(Lexer const &);
};

#endif //LEXER_H
