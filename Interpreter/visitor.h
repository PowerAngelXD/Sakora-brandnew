#ifndef SAKORA_VISITOR_H
#define SAKORA_VISITOR_H

#include "../Frontend/Parser/parser.h"
#include "instruction.h"

namespace sakora {
    using CodeSequence = std::vector<VMCode>;

    class CodeMaker {
    public:
        static VMCode PUSH(std::string value, int ln, int col);
        static VMCode ADD();
        static VMCode SUB();
        static VMCode MUL();
        static VMCode DIV();
        static VMCode LGC_AND();
        static VMCode LGC_OR();
        static VMCode LGC_NOT_EQU();
        static VMCode LGC_EQU();
        static VMCode LGC_MR_THAN();
        static VMCode LGC_LS_THAN();
        static VMCode LGC_MREQU_THAN();
        static VMCode LGC_LSEQU_THAN();
        static VMCode LGC_NOT();
        static VMCode ARR_MAKE(std::string size, int ln, int col);
        static VMCode ARR_TIDY_CHK(int ln, int col);
        static VMCode DECLARE(std::string name, int ln, int col);
        static VMCode ASSIGN(std::string name, int ln, int col);
        static VMCode GET(std::string name, int ln, int col);
        static VMCode FROM(std::string type, int ln, int col);
        static VMCode NEW_SCOPE();
        static VMCode END_SCOPE();
        static VMCode FLAG(std::string flag_name);
        static VMCode JTIN();
        static VMCode JTBCK();
    };

    class Visitor {
    public:
        CodeSequence seq;

        void make(VMCode code);


        void visit(AST::BasicIdentifierNode node);
        void visit(AST::AtomIdentifierNode node);
        void visit(AST::IdentifierExprNode node);
        void visit(AST::PrimExprNode node);
        void visit(AST::MulExprNode node);
        void visit(AST::AddExprNode node);
        void visit(AST::LogicExprNode node);
        void visit(AST::BoolExprNode node);
        void visit(AST::PrimTypeExprNode node);
        void visit(AST::ArrayTypeExprNode node);
        void visit(AST::TypeExprNode node);
        void visit(AST::ArrayExprNode node);
        void visit(AST::WholeExprNode node);

        void visit(AST::LetStmtNode node);
        void visit(AST::AssignStmtNode node);
        void visit(AST::BlockStmtNode node, bool jmpCond = false);
        void visit(AST::IfStmtNode node);
        void visit(AST::ElseIfStmtNode node);
        void visit(AST::ElseStmtNode node);
        void visit(AST::MatchStmtNode node);
        void visit(AST::WhileStmtNode node);
        void visit(AST::ExprStmtNode node);

        void visit(AST::StmtNode node);
    };
}

#endif