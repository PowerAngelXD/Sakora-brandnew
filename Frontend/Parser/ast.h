#ifndef SAKORA_AST_EXPR_H
#define SAKORA_AST_EXPR_H

#include "../Lexer/lexer.h"
#include <memory>
#include <sstream>

namespace AST {
    class Node {
    public:
        virtual std::string toString();
    };


    // Expression

    class WholeExprNode;
    class AddExprNode;
    class TypeExprNode;
    class ArrayExprNode;
    class IdentifierExprNode;
    class StmtNode;

    class BasicIdentifierNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> iden = nullptr;
        
        struct CallingOp {
            std::shared_ptr<Lexer::Token> left = nullptr;
            std::vector<std::shared_ptr<WholeExprNode>> args;
            std::vector<std::shared_ptr<Lexer::Token>> dots;
            std::shared_ptr<Lexer::Token> right = nullptr;
        };

        std::shared_ptr<CallingOp> callOp = nullptr;
        std::shared_ptr<Lexer::Token> selfOp = nullptr; // +=，-=，*=， /=， ++， --这种操作符
        std::shared_ptr<AddExprNode> selfExpr = nullptr;

        std::string toString() override;
    };

    class AtomIdentifierNode : public Node {
    public:
        std::shared_ptr<BasicIdentifierNode> iden = nullptr;
        
        struct getIndexOp {
            std::shared_ptr<Lexer::Token> left = nullptr;
            std::shared_ptr<AddExprNode> index;
            std::shared_ptr<Lexer::Token> right = nullptr;
        };

        std::vector<std::shared_ptr<getIndexOp>> getIndexOps;

        std::string toString() override;
    };

    class IdentifierExprNode : public Node {
    public:
        std::vector<std::shared_ptr<AtomIdentifierNode>> idens;
        std::vector<std::shared_ptr<Lexer::Token>> getOps;

        std::string toString() override;
    };

    class PrimExprNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> prefixOp = nullptr;

        std::shared_ptr<Lexer::Token> literal = nullptr;
        std::shared_ptr<IdentifierExprNode> iden = nullptr;
        std::shared_ptr<ArrayExprNode> arrayExpr = nullptr;
        std::shared_ptr<WholeExprNode> wholeExpr = nullptr;

        std::string toString() override;
    };

    class MulExprNode : public Node {
    public:
        std::vector<std::shared_ptr<PrimExprNode>> prims;
        std::vector<std::shared_ptr<Lexer::Token>> ops;

        std::string toString() override;
    };

    class AddExprNode : public Node {
    public:
        std::vector<std::shared_ptr<MulExprNode>> muls;
        std::vector<std::shared_ptr<Lexer::Token>> ops;

        std::string toString() override;
    };

    class LogicExprNode : public Node {
    public:
        std::vector<std::shared_ptr<AddExprNode>> adds;
        std::vector<std::shared_ptr<Lexer::Token>> ops;

        std::string toString() override;
    };

    class BoolExprNode : public Node {
    public:
        std::vector<std::shared_ptr<LogicExprNode>> lgcs;
        std::vector<std::shared_ptr<Lexer::Token>> ops;

        std::string toString() override;
    };

    class PrimTypeExprNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> identifier = nullptr;

        std::string toString() override;
    };

    class ArrayTypeExprNode : public Node {
    public:
        struct ArrayInfoOpNode {
            std::shared_ptr<Lexer::Token> leftArrayModOp = nullptr;
            std::shared_ptr<Lexer::Token> length = nullptr;
            std::shared_ptr<Lexer::Token> rightArrayModOp = nullptr;
        };

        std::shared_ptr<PrimTypeExprNode> primType = nullptr;
        std::vector<std::shared_ptr<ArrayInfoOpNode>> arrayInfos;
        

        std::string toString() override;
    };

    class TypeExprNode : public Node {
    public:
        std::shared_ptr<PrimTypeExprNode> prim = nullptr;
        std::shared_ptr<ArrayTypeExprNode> array = nullptr;

        std::string toString() override;
    };

    class ArrayExprNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> leftArrayModOp = nullptr;
        std::vector<std::shared_ptr<AddExprNode>> elements;
        std::vector<std::shared_ptr<Lexer::Token>> dots;
        std::shared_ptr<Lexer::Token> rightArrayModOp = nullptr;

        std::string toString() override;
    };

    class WholeExprNode : public Node {
    public:
        std::shared_ptr<AddExprNode> addExpr = nullptr;
        std::shared_ptr<BoolExprNode> boolExpr = nullptr;
        std::shared_ptr<TypeExprNode> typeExpr = nullptr;

        std::string toString() override;
    };


    // Statement

    class LetStmtNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> letMark = nullptr;
        std::shared_ptr<Lexer::Token> identifier = nullptr;

        // Optional
        std::shared_ptr<Lexer::Token> typeModOp = nullptr;
        std::shared_ptr<TypeExprNode> type = nullptr;
        //

        std::shared_ptr<Lexer::Token> assignOp = nullptr;
        std::shared_ptr<WholeExprNode> expr = nullptr;

        std::shared_ptr<Lexer::Token> stmtEndOp = nullptr;

        std::string toString() override;
    };

    class AssignStmtNode : public Node {
    public:
        std::shared_ptr<IdentifierExprNode> iden = nullptr;
        std::shared_ptr<Lexer::Token> assignOp = nullptr;
        std::shared_ptr<WholeExprNode> expr = nullptr;

        std::shared_ptr<Lexer::Token> stmtEndOp = nullptr;

        std::string toString() override;
    };

    class BlockStmtNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> leftBrace = nullptr;
        std::vector<std::shared_ptr<StmtNode>> body;
        std::shared_ptr<Lexer::Token> rightBrace = nullptr;

        std::string toString() override;
    };

    // Stage1
    class ElseIfStmtNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> elseMark = nullptr;
        std::shared_ptr<Lexer::Token> ifMark = nullptr;

        std::shared_ptr<Lexer::Token> left = nullptr;
        std::shared_ptr<BoolExprNode> condition = nullptr;
        std::shared_ptr<Lexer::Token> right = nullptr;

        std::shared_ptr<BlockStmtNode> bodyBlock = nullptr;

        std::string toString() override;
    };

    class ElseStmtNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> elseMark = nullptr;

        std::shared_ptr<BlockStmtNode> bodyBlock = nullptr;

        std::string toString() override;
    };
    class IfStmtNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> ifMark = nullptr;

        std::shared_ptr<Lexer::Token> left = nullptr;
        std::shared_ptr<BoolExprNode> condition = nullptr;
        std::shared_ptr<Lexer::Token> right = nullptr;

        std::shared_ptr<BlockStmtNode> bodyBlock = nullptr;

        std::vector<std::shared_ptr<ElseIfStmtNode>> elseIfstmts;
        std::shared_ptr<ElseStmtNode> elseStmt = nullptr;

        std::string toString() override;
    };

    class MatchStmtNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> matchMark = nullptr;
        std::shared_ptr<Lexer::Token> left = nullptr;
        std::shared_ptr<IdentifierExprNode> identifier = nullptr;
        std::shared_ptr<Lexer::Token> right = nullptr;

        std::shared_ptr<Lexer::Token> leftBrace = nullptr;
        struct matchBlock {
            std::shared_ptr<WholeExprNode> caseExpr = nullptr;
            std::shared_ptr<Lexer::Token> caseOp = nullptr;
            std::shared_ptr<BlockStmtNode> bodyBlock = nullptr;
        };
        std::vector<std::shared_ptr<matchBlock>> matchBlocks;

        std::shared_ptr<Lexer::Token> defaultMark = nullptr;
        std::shared_ptr<Lexer::Token> defaultOp = nullptr;
        std::shared_ptr<BlockStmtNode> defaultBlock = nullptr;

        std::shared_ptr<Lexer::Token> rightBrace = nullptr;

        std::string toString() override;
    };

    class WhileStmtNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> whileMark = nullptr;
        std::shared_ptr<Lexer::Token> left = nullptr;
        std::shared_ptr<BoolExprNode> condition = nullptr;
        std::shared_ptr<Lexer::Token> right = nullptr;

        std::shared_ptr<BlockStmtNode> bodyBlock = nullptr;

        std::string toString() override;
    };

    class RepeatStmtNode : public Node {};

    class ExprStmtNode : public Node {
    public:
        std::shared_ptr<IdentifierExprNode> idenExpr = nullptr;

        std::shared_ptr<Lexer::Token> stmtEndOp = nullptr;

        std::string toString() override;
    };

    class FuncDefineStmtNode : public Node {};

    // Stage2
    class StructDefineStmtNode : public Node {};

    class ImplStmtNode : public Node {};

    class StmtNode : public Node {
    public:
        std::shared_ptr<LetStmtNode> letStmt = nullptr;
        std::shared_ptr<AssignStmtNode> assignStmt = nullptr;
        std::shared_ptr<IfStmtNode> ifStmt = nullptr;
        std::shared_ptr<ElseIfStmtNode> elseIfStmt = nullptr;
        std::shared_ptr<ElseStmtNode> elseStmt = nullptr;
        std::shared_ptr<BlockStmtNode> blockStmt = nullptr;
        std::shared_ptr<MatchStmtNode> matchStmt = nullptr;
        std::shared_ptr<WhileStmtNode> whileStmt = nullptr;
        std::shared_ptr<ExprStmtNode> exprStmt = nullptr;

        std::string toString() override;
    };
}

#endif