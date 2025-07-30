#ifndef SAKORA_GENERATOR_H
#define GENERATOR_H

#include "../Parser/parser.h"
#include "../../Backend/ins.h"

class Generator {
    std::vector<INS::Instruction> insSet;
public:

    void generate(AST::PrimExprNode node);
    void generate(AST::MulExprNode node);
    void generate(AST::AddExprNode node);
    void generate(AST::WholeExprNode node);
};

#endif