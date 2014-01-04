#ifndef PARSER_H
#define PARSER_H

#include <tr1/memory>
#include <vector>
#include "ast.h"
#include "lexer.h"
#include "programContext.h"

using std::tr1::shared_ptr;

struct Parser
{
    Parser(istream &sourceStream):
        lexer(sourceStream)
    {}

    ProgramContext parse(){
        return parseProgram();
    }

    size_t getLine() const{
        return lexer.getLineNumber();
    }
private:
    Lexer lexer;

    ProgramContext parseProgram();
    InstructionPtr parseInstruction();
    InstructionPtr parsePlusMinus();
    InstructionPtr parseMultDiv();
    InstructionPtr parseId();
    InstructionPtr parseNum();
    InstructionPtr parseVarDef();
    InstructionPtr parseValue();
    InstructionPtr parseIf();
    InstructionPtr parseWhile();
    InstructionPtr parseReturn();
    InstructionPtr parseCond();
    InstructionPtr parseRead();
    InstructionPtr parsePrint();
    FunPtr parseFunDef();
};

#endif // PARSER_H
