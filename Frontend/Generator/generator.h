#ifndef SAKORA_GENERATOR_H
#define GENERATOR_H

#include "../Parser/parser.h"
#include "../../Backend/ins.h"

class Generator {
public:
    std::vector<INS::Instruction> insSet;

    void generate(AST::PrimExprNode node);
    void generate(AST::MulExprNode node);
    void generate(AST::AddExprNode node);
    void generate(AST::LogicExprNode node);
    void generate(AST::BoolExprNode node);
    void generate(AST::PrimTypeExprNode node);
    void generate(AST::ArrayTypeExprNode node);
    void generate(AST::TypeExprNode node);
    void generate(AST::WholeExprNode node);
};

#endif