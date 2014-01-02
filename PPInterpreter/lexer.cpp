#include "lexer.h"

bool Lexer::checkToken(Token::Type t, size_t steps){
    Token token;
    for (size_t i = 0; i != steps; ++i)
        token = nextToken();
    return (token.type == t);
}

Token Lexer::nextToken(){
    char peek = sourceStream.get();
    while (!sourceStream.eof() && isspace(peek) && peek != '\n')
        peek = sourceStream.get();

    if (sourceStream.eof()) return Token::Eof;

    if (peek == '#')
        while (peek != '\n')
            peek = sourceStream.get();
    sourceStream.putback(peek);

    Token res = getSymbol();
    if (res.type == Token::WTF)
        res = getNumber();
    if (res.type == Token::WTF)
        res = getIdentifier();
    return res;
}

Token Lexer::getIdentifier(){
    char peek = sourceStream.get();

    if (!isalpha(peek)){
        sourceStream.putback(peek);
        return Token::WTF;
    }

    string temp;
    temp.push_back(peek);
    while (isalpha(sourceStream.peek()) || isdigit(peek) || peek == '_')
        temp.push_back(sourceStream.get());

    if (temp == "def")
        return Token::DEF;
    if (temp == "return")
        return Token::RET;
    if (temp == "end")
        return Token::END;
    if (temp == "while")
        return Token::WHILE;
    if (temp == "if")
        return Token::IF;
    if (temp == "print")
        return Token::PRINT;
    if (temp == "read")
        return Token::READ;
    return Token(Token::VAR, 0, temp);
}

Token Lexer::getNumber(){
    char peek = sourceStream.get();

    if (!isdigit(peek)){
        sourceStream.putback(peek);
        return Token::WTF;
    }

    string number;
    number.push_back(peek);
    while (isdigit(sourceStream.peek()))
        number.push_back(sourceStream.get());

    long num = atol(number.c_str());
    return Token(Token::NUM, num);
}

Token Lexer::getSymbol(){
    char peek = sourceStream.get();
    char next = 0;

    switch (peek) {
    case '(':
        return Token::LP;
    case ')':
        return Token::RP;
    case '+':
        return Token::PLUS;
    case '-':
        return Token::MINUS;
    case '*':
        return Token::MULT;
    case '/':
        return Token::DIV;
    case ':':
        return Token::COL;
    case ',':
        return Token::COM;
    case '\n':
        ++currentLine;
        return Token::CR;
    case '=':
        next = sourceStream.get();
        if (next == '=') {
            return Token::EQ;
        } else {
            sourceStream.putback(next);
            return Token::ASGN;
        }
    case '!':
        next = sourceStream.get();
        if (next == '=') {
            return Token::NE;
        } else {
            return Token::WTF;
        }
    case '>': {
        next = sourceStream.get();
        if (next == '=') {
            return Token::GE;
        } else {
            sourceStream.putback(next);
            return Token::GT;
        }
    }
    case '<': {
        next = sourceStream.get();
        if (next == '=') {
            return Token::LE;
        } else {
            sourceStream.putback(next);
            return Token::LT;
        }
    }
    default:{
        sourceStream.putback(peek);
        return Token::WTF;
    }
    }
}

