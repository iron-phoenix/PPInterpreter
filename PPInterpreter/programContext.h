#ifndef PROGRAMCONTEXT_H
#define PROGRAMCONTEXT_H

#include <map>
#include <string>
#include "ast.h"

using std::map;
using std::string;

typedef shared_ptr<FunDef> FunPtr;

struct ProgramContext {
    InstructionPtr entryPoint;
    map<string, FunPtr> functions;

    ProgramContext(InstructionPtr const &entryPoint, map<string, FunPtr> functions):
        entryPoint(entryPoint),
        functions(functions)
    {}
};

#endif // PROGRAMCONTEXT_H
