#ifndef SAKORA_GENERATOR_H
#define GENERATOR_H

#include "../Parser/parser.h"
#include "../../Backend/ins.h"

class Generator {
public:
    std::vector<INS::Instruction> insSet;

    void generate(AST::AtomIdentifierNode node, bool pushObj = false);
    void generate(AST::IdentifierExprNode node);
    void generate(AST::PrimExprNode node);
    void generate(AST::MulExprNode node);
    void generate(AST::AddExprNode node);
    void generate(AST::LogicExprNode node);
    void generate(AST::BoolExprNode node);
    void generate(AST::PrimTypeExprNode node);
    void generate(AST::ArrayTypeExprNode node);
    void generate(AST::TypeExprNode node);
    void generate(AST::ArrayExprNode node);
    void generate(AST::WholeExprNode node);

    void generate(AST::LetStmtNode node);
    void generate(AST::AssignStmtNode node);
    void generate(AST::BlockStmtNode node, bool jmpCond = false);
    void generate(AST::IfStmtNode node);
    void generate(AST::ElseIfStmtNode node);
    void generate(AST::ElseStmtNode node);
    void generate(AST::MatchStmtNode node);

    void generate(AST::StmtNode node);
};

#endif