#include "parser.h"

ProgramContext Parser::parseProgram(){
    Instructions instructions;
    map<string, FunPtr> functions;
    while (!lexer.checkToken(Token::Eof)) {
        InstructionPtr instruction = parseInstruction();
        if (instruction) {
            instructions.push_back(instruction);
            continue;
        }

        FunPtr funDef = parseFunDef();
        if (funDef) {
            functions[funDef->getName()] = funDef;
            continue;
        }
    }

    return ProgramContext(InstructionPtr(new Program(instructions, instructions.at(0)->getLineNumber())), functions);
}

InstructionPtr Parser::parseInstruction(){
    while (lexer.checkToken(Token::CR)) lexer.nextToken();

    InstructionPtr res = parseRead();
    if (!res) res = parsePrint();
    if (!res) res = parseVarDef();
    if (!res) res = parsePlusMinus();
    if (!res) res = parseIf();
    if (!res) res = parseWhile();
    if (!res) res = parseReturn();
    if (res) while (lexer.checkToken(Token::CR)) lexer.nextToken();

    return res;
}

InstructionPtr Parser::parsePlusMinus(){
    InstructionPtr left = parseMultDiv();
    if (!left) return InstructionPtr();

    if (!lexer.checkToken(Token::PLUS) && !lexer.checkToken(Token::MINUS)) return left;
    Token op = lexer.nextToken();

    InstructionPtr right = parsePlusMinus();
    if (!right){
        //TODO gen error
    }

    switch (op.type) {
    case Token::PLUS: return InstructionPtr(new Operator('+', left, right, lexer.getLineNumber()));
    case Token::MINUS: return InstructionPtr(new Operator('-', left, right, lexer.getLineNumber()));
    default:{
        //TODO gen error
    }
    }
}

InstructionPtr Parser::parseMultDiv(){
    InstructionPtr left = parseValue();
    if (!left) return InstructionPtr();

    if (!lexer.checkToken(Token::MULT) && !lexer.checkToken(Token::DIV)) return left;
    Token op = lexer.nextToken();

    InstructionPtr right = parseMultDiv();
    if (!right){
        //TODO gen error
    }

    switch (op.type) {
    case Token::MULT: return InstructionPtr(new Operator('*', left, right, lexer.getLineNumber()));
    case Token::DIV: return InstructionPtr(new Operator('/', left, right, lexer.getLineNumber()));
    default:{
        //TODO gen error
    }
    }
}

InstructionPtr Parser::parseId(){
    if (!lexer.checkToken(Token::ID)) return InstructionPtr();

    string id = lexer.nextToken().name;
    if (!lexer.checkToken(Token::LP)) return InstructionPtr(new Var(id, lexer.getLineNumber()));
    lexer.nextToken();

    Instructions functionParams;
    if (!lexer.checkToken(Token::RP)) {
        while(true) {
            InstructionPtr p = parsePlusMinus();
            if (!p){
                //TODO gen error
            }
            functionParams.push_back(p);
            if (lexer.checkToken(Token::COM)) lexer.nextToken();
            else break;
        }
        if (!lexer.checkToken(Token::RP)){
            //TODO gen error
        }
    }
    lexer.nextToken();

    return InstructionPtr(new FunCall(id, functionParams, lexer.getLineNumber()));
}

InstructionPtr Parser::parseNum(){
    if (lexer.checkToken(Token::NUM)) {
        Token t = lexer.nextToken();
        return InstructionPtr(new Num(t.value, lexer.getLineNumber()));
    }
    return InstructionPtr();
}

InstructionPtr Parser::parseVarDef(){
    if (!lexer.checkToken(Token::ID) || lexer.checkToken(Token::LP, 2)) return InstructionPtr();
    string id = lexer.nextToken().name;

    if (lexer.nextToken().type != Token::ASGN){
        //TODO gen error
    }

    InstructionPtr exp = parsePlusMinus();
    if (!exp){
        //TODO gen error
    }

    return InstructionPtr(new VarDef(id, exp, lexer.getLineNumber()));
}

InstructionPtr Parser::parseValue(){
    if (lexer.checkToken(Token::MINUS)) {
        lexer.nextToken();
        InstructionPtr val = parseValue();
        if (!val){
            //TODO gen error
        }
        InstructionPtr zero = InstructionPtr(new Num(0, 0));
        return InstructionPtr(new Operator('-', zero, val, lexer.getLineNumber()));
    }

    if (lexer.checkToken(Token::LP)) {
        lexer.nextToken();
        InstructionPtr exp = parsePlusMinus();
        if (!exp || lexer.nextToken().type != Token::RP){
            //TODO gen error
        }
        return exp;
    }

    InstructionPtr val = parseNum();
    if (!val) val = parseId();

    return val;
}

InstructionPtr Parser::parseIf(){
    if (!lexer.checkToken(Token::IF)) return InstructionPtr();
    lexer.nextToken();

    InstructionPtr cond = parseCond();
    if (!cond || lexer.nextToken().type != Token::COL || lexer.nextToken().type != Token::CR){
        //TODO gen error
    }

    Instructions instructions;
    while (!lexer.checkToken(Token::END)) {
        InstructionPtr instruction = parseInstruction();
        if (!instruction){
            //TODO gen error
        }
        instructions.push_back(instruction);
    }
    lexer.nextToken();

    return InstructionPtr(new If(cond, instructions, lexer.getLineNumber()));
}

InstructionPtr Parser::parseWhile(){
    if (!lexer.checkToken(Token::WHILE)) return InstructionPtr();
    lexer.nextToken();

    InstructionPtr cond = parseCond();
    if (!cond || lexer.nextToken().type != Token::COL || lexer.nextToken().type != Token::CR){
        //TODO gen error
    }

    Instructions instructions;
    while (!lexer.checkToken(Token::END)) {
        InstructionPtr instruction = parseInstruction();
        if (!instruction){
            //TODO gen error
        }
        instructions.push_back(instruction);
    }
    lexer.nextToken();

    return InstructionPtr(new While(cond, instructions, lexer.getLineNumber()));
}

InstructionPtr Parser::parseReturn(){
    if (!lexer.checkToken(Token::RET)) return InstructionPtr();
    lexer.nextToken();

    InstructionPtr exp = parsePlusMinus();
    if (!exp){
        //TODO gen error
    }
    return InstructionPtr(new Return(exp, lexer.getLineNumber()));
}

InstructionPtr Parser::parseCond(){
    InstructionPtr left = parsePlusMinus();
    if (!left) return InstructionPtr();

    Token ct = lexer.nextToken();
    if (ct.type != Token::EQ && ct.type != Token::NE && ct.type != Token::LT && ct.type != Token::GT && ct.type != Token::LE && ct.type != Token::GE){
        //TODO gen error
    }

    InstructionPtr right = parsePlusMinus();
    if (!right){
        //TODO gen error
    }

    string sign;
    switch (ct.type) {
    case Token::EQ: sign = "=="; break;
    case Token::NE: sign = "!="; break;
    case Token::GT: sign = ">"; break;
    case Token::LT: sign = "<"; break;
    case Token::GE: sign = ">="; break;
    case Token::LE: sign = "<="; break;
    };

    return InstructionPtr(new Cond(left, right, sign, lexer.getLineNumber()));
}

InstructionPtr Parser::parseRead()
{
    if (!lexer.checkToken(Token::READ)) return InstructionPtr();
    lexer.nextToken();

    Token var = lexer.nextToken();
    if (var.type != Token::ID){
        //TODO gen error
    }

    return InstructionPtr(new Read(var.name, lexer.getLineNumber()));
}

InstructionPtr Parser::parsePrint(){
    if (!lexer.checkToken(Token::PRINT)) return InstructionPtr();
    lexer.nextToken();

    InstructionPtr exp = parsePlusMinus();
    if (!exp){
        //TODO gen error
    }

    return InstructionPtr(new Print(exp, lexer.getLineNumber()));
}

FunPtr Parser::parseFunDef(){
    if (!lexer.checkToken(Token::DEF)) return FunPtr();
    lexer.nextToken();

    Token functionName = lexer.nextToken();
    if (functionName.type != Token::ID || lexer.nextToken().type != Token::LP){
        //TODO gen error
    }

    vector<string> functionParams;
    if (!lexer.checkToken(Token::RP)) {
        while(true) {
            Token p = lexer.nextToken();
            if (p.type != Token::ID){
                //TODO gen error
            }
            functionParams.push_back(p.name);
            if (lexer.checkToken(Token::COM)) lexer.nextToken();
            else break;
        }
        if (!lexer.checkToken(Token::RP)){
            //TODO gen error
        }
    }
    lexer.nextToken();

    if (lexer.nextToken().type != Token::COL || lexer.nextToken().type != Token::CR){
        //TODO gen error
    }

    Instructions instructions;
    while (!lexer.checkToken(Token::END)) {
        InstructionPtr instruction = parseInstruction();
        instructions.push_back(instruction);
        continue;
    }
    lexer.nextToken();

    if (lexer.nextToken().type != Token::CR){
        //TODO gen error
    }

    return FunPtr(new FunDef(functionName.name, functionParams, instructions, lexer.getLineNumber()));
}
