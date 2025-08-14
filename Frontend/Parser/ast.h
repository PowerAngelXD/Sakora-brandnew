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
    class TypeExprNode;
    class ArrayExprNode;

    class PrimExprNode : public Node {
    public:
        std::shared_ptr<Lexer::Token> prefixOp = nullptr;

        std::shared_ptr<Lexer::Token> literal = nullptr;
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
}

#endif