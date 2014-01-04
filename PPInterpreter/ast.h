#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <tr1/memory>
#include "lexer.h"
#include "visitor.h"

using std::string;
using std::vector;
using std::tr1::shared_ptr;

struct Instruction;

typedef shared_ptr<Instruction> InstructionPtr;
typedef vector<InstructionPtr> Instructions;

struct Instruction {
    Instruction(size_t lineNumber) : lineNumber(lineNumber) {}
    virtual ~Instruction() {}

    size_t getLineNumber() const{
        return lineNumber;
    }

    virtual int accept(Visitor &) = 0;

private:
    size_t lineNumber;
};

struct InstructionList: public Instruction {
    InstructionList(Instructions const &instructions, size_t lineNumber):
        Instruction(lineNumber),
        instructions(instructions)
    {}

    Instructions const &getInstructions() const{
        return instructions;
    }

private:
    Instructions instructions;
};

struct Program: public InstructionList {
    Program(Instructions const &instructions, size_t lineNumber):
        InstructionList(instructions, lineNumber)
    {}

    int accept(Visitor &v){
        return v.visit(*this);
    }
};

struct FunDef: public InstructionList {
    FunDef(string const &name, vector<string> const &params, Instructions const &instructions, size_t lineNumber):
        InstructionList(instructions, lineNumber),
        name(name),
        params(params)
    {}

    string const &getName() const{
        return name;
    }

    vector<string> const &getParams() const{
        return params;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    string name;
    vector<string> params;
};

struct VarDef: public Instruction {
    VarDef(string const &name, InstructionPtr exp, size_t lineNumber):
        Instruction(lineNumber),
        name(name),
        exp(exp)
    {}

    string const &getName() const{
        return name;
    }

    InstructionPtr getExp() const{
        return exp;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    string name;
    InstructionPtr exp;
};

struct Num: public Instruction {
    Num(int value, size_t lineNumber):
        Instruction(lineNumber),
        value(value)
    {}

    int getValue() const{
        return value;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    int value;
};

struct Var: public Instruction {
    Var(string const &name, size_t lineNumber):
        Instruction(lineNumber),
        name(name)
    {}

    string const &getName() const{
        return name;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
        string name;
};

struct FunCall: public Instruction {
    FunCall(string const &name, Instructions const &params, size_t lineNumber):
        Instruction(lineNumber),
        name(name),
        params(params)
    {}

    string const &getName() const{
        return name;
    }

    Instructions const &getParams() const{
        return params;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    string name;
    Instructions params;
};

struct Operator: public Instruction {
    Operator(const char op, InstructionPtr left, InstructionPtr right, size_t lineNumber):
        Instruction(lineNumber),
        operation(op),
        left(left),
        right(right)
    {}

    char getOperation() const{
        return operation;
    }

    InstructionPtr getLeft() const{
        return left;
    }

    InstructionPtr getRight() const{
        return right;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    char operation;
    InstructionPtr left;
    InstructionPtr right;
};

struct Read: public Instruction {
    Read(string const &var, size_t lineNumber):
        Instruction(lineNumber),
        var(var)
    {}

    string const &getVar() const{
        return var;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    string var;
};

struct Print: public Instruction {
    Print(InstructionPtr exp, size_t lineNumber):
        Instruction(lineNumber),
        exp(exp)
    {}

    InstructionPtr getExp() const{
        return exp;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    InstructionPtr exp;
};

struct Cond: public Instruction {
    Cond(InstructionPtr left, InstructionPtr right, string comp, size_t lineNumber):
        Instruction(lineNumber),
        left(left),
        right(right),
        comparison(comp)
    {}

    string getComparison() const{
        return comparison;
    }

    InstructionPtr getLeft() const{
        return left;
    }

    InstructionPtr getRight() const{
        return right;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    InstructionPtr left;
    InstructionPtr right;
    string comparison;
};

struct If: public InstructionList {
    If(InstructionPtr cond, Instructions const &instructions, size_t lineNumber):
        InstructionList(instructions, lineNumber),
        cond(cond)
    {}

    InstructionPtr getCond() const{
        return cond;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    InstructionPtr cond;
};

struct While: public InstructionList {
    While(InstructionPtr cond, Instructions const &instructions, size_t lineNumber):
        InstructionList(instructions, lineNumber),
        cond(cond)
    {}

    InstructionPtr getCond() const{
        return cond;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    InstructionPtr cond;
};

struct Return: public Instruction {
    Return(InstructionPtr exp, size_t lineNumber):
        Instruction(lineNumber),
        exp(exp)
    {}

    InstructionPtr getExp() const{
        return exp;
    }

    int accept(Visitor &v){
        return v.visit(*this);
    }

private:
    InstructionPtr exp;
};

#endif // AST_H
