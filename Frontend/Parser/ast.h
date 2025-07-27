#ifndef AST_EXPR_H
#define AST_EXPR_H

#define InitBranchs std::make_shared<std::vector<AST::Node>>()

#include "../Lexer/lexer.h"
#include <memory>

namespace AST {
    // 区分各个Node的类型，parser根据这个来生成对应的Node
    enum NodeType {
        NoneNode, Value, Op, Branch, 
        PrimExpr, MulExpr, AddExpr, WholeExpr
    };

    struct Node {
        NodeType type;

        Lexer::Token content;
        std::vector<Node> branchs;

        Node(NodeType t);
        Node(NodeType t, Lexer::Token c);
    };

    std::string nodeToString(Node n);
    std::string noneToString(Node n);

    std::string primExprToString(Node n);
    std::string mulExprToString(Node n);
    std::string addExprToString(Node n);
    std::string wholeExprToString(Node n);
}

#endif