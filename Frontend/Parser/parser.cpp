#include "parser.h"

Parser::Parser(Lexer::TokenSequence s) {
    seq = s;
}

Lexer::Token Parser::peek()
{
    return seq.at(index);
}

Lexer::Token Parser::eat() {
    return seq.at(index ++);
}

std::shared_ptr<Lexer::Token> Parser::eatAsPtr() {
    return std::make_shared<Lexer::Token>(eat());
}


// 目前的表达式仅支持数字计算
bool Parser::isPrimExpr() {
    return peek().type == Lexer::Number || peek().content == "(";
}

bool Parser::isAddExpr() {
    return isPrimExpr();
}

bool Parser::isMulExpr() {
    return isAddExpr();
}

/*
    PrimExpr:
    if is WholeExpr (has '()'):
        branchs:
            0 -> '('
            1 -> wholeExpr
            2 -> ')'
    else:
        content:
            value
*/
AST::Node Parser::parsePrimExpr() {
    if (!isPrimExpr()) {
        // TODO: ERROR
    }

    if (peek().content == "(") {
        AST::Node node(AST::WholeExpr);

        node.branchs.emplace_back(AST::Node(AST::Op, eat()));
        node.branchs.emplace_back(parseWholeExpr());

        if (peek().content != ")") { 
            // TODO: ERROR
        }
        else node.branchs.emplace_back(AST::Node(AST::Op, eat()));

        return node;
    }
    else if (peek().type == Lexer::Number) {
        AST::Node node(AST::Value);

        node.content = eat();

        return node;
    }
    else return { AST::NoneNode };
}

/*
    MulExpr:
    branchs:
        0 -> primExprs
        1 -> ops
    tips: 当MulExpr没有运算符的时候就是一个字面量，没有branch[1]
*/
AST::Node Parser::parseMulExpr() {
    if (!isMulExpr()) {
        // TODO: ERROR
    }

    AST::Node node = { AST::MulExpr };

    node.branchs.emplace_back(AST::Node(AST::Branch)); // 0 -> primExprs

    bool hasOp = false;

    node.branchs.at(0).branchs.emplace_back(parsePrimExpr());
    while (peek().type == Lexer::Symbol && (peek().content == "*" || peek().content == "/")) {
        if (!hasOp) {
            node.branchs.emplace_back(AST::Node(AST::Branch)); // 1 -> ops
        }
        hasOp = true;
        node.branchs.at(1).branchs.emplace_back(AST::Node(AST::Op, eat()));

        if (!isPrimExpr()) {
            // TODO: ERROR
        }

        node.branchs.at(0).branchs.emplace_back(parsePrimExpr());
    }

    return node;
}

/*
    AddExpr:
    branchs:
        0 -> mulExprs
        1 -> ops

*/
AST::Node Parser::parseAddExpr() {
    if (!isAddExpr()) {
        // TODO: ERROR
    }

    AST::Node node = { AST::AddExpr };

    node.branchs.emplace_back(AST::Node(AST::Branch)); // 0 -> mulExprs

    bool hasOp = false;

    node.branchs.at(0).branchs.emplace_back(parseMulExpr());
    while (peek().type == Lexer::Symbol && (peek().content == "+" || peek().content == "-")) {
        if (!hasOp) {
            node.branchs.emplace_back(AST::Node(AST::Branch)); // 1 -> ops
        }
        hasOp = true;
        node.branchs.at(1).branchs.emplace_back(AST::Node(AST::Op, eat()));

        if (!isPrimExpr()) {
            // TODO: ERROR
        }

        node.branchs.at(0).branchs.emplace_back(parseMulExpr());
    }

    if (!hasOp) {
        // TODO: ERROR
    }

    return node;
}

AST::Node Parser::parseWholeExpr() {
    if (isAddExpr()) return parseAddExpr();
    else return { AST::NoneNode };
}

