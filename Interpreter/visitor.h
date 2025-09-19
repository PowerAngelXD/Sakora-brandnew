#ifndef SAKORA_VISITOR_H
#define SAKORA_VISITOR_H

#include "../Frontend/Parser/parser.h"
#include "instruction.h"


#define BLK_START make(CodeMaker::blockStart());
#define BLK_END make(CodeMaker::blockEnd());
#define JMPTIN make(CodeMaker::jtin());
#define JMPTBCK make(CodeMaker::jtbck());
#define LGC_AND make(CodeMaker::lgcAnd());
#define LGC_OR make(CodeMaker::lgcOr());
#define LGC_EQU make(CodeMaker::lgcEqu());
#define LGC_NOT_EQU make(CodeMaker::lgcNotEqu());
#define LGC_NOT make(CodeMaker::lgcNot());
#define LGC_MR_THAN make(CodeMaker::lgcMrThan());
#define LGC_LS_THAN make(CodeMaker::lgcLsThan());
#define LGC_MREQU_THAN make(CodeMaker::lgcMrEquThan());
#define LGC_LSEQU_THAN make(CodeMaker::lgcLsEquThan());

#define ADD make(CodeMaker::add());
#define SUB make(CodeMaker::sub());
#define MUL make(CodeMaker::mul());
#define DIV make(CodeMaker::div());


namespace sakora {
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
        void visit(AST::ElseStmtNode node);
        void visit(AST::MatchStmtNode node);
        void visit(AST::WhileStmtNode node);
        void visit(AST::ExprStmtNode node);

        void visit(AST::StmtNode node);
    };
}

#endif