#ifndef VISITOR_H
#define VISITOR_H

class Visitor {
public:
    virtual int visit(class Program const &node) = 0;
    virtual int visit(class FunDef const &node) = 0;
    virtual int visit(class VarDef const &node) = 0;
    virtual int visit(class Num const &node) = 0;
    virtual int visit(class Var const &node) = 0;
    virtual int visit(class FunCall const &node) = 0;
    virtual int visit(class Operator const &node) = 0;
    virtual int visit(class Cond const &node) = 0;
    virtual int visit(class If const &node) = 0;
    virtual int visit(class While const &node) = 0;
    virtual int visit(class Return const &node) = 0;
    virtual int visit(class Read const &node) = 0;
    virtual int visit(class Print const &node) = 0;
};

#endif // VISITOR_H
