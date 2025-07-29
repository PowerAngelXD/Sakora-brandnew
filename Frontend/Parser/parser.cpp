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

std::shared_ptr<AST::PrimExprNode> Parser::parsePrimExpr() {
    if(!isPrimExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Literal Or Expression", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::PrimExprNode>();
    if (peek().content == "(") {
        eat();
        node->wholeExpr = parseWholeExpr();
        eat();
        return node;
    }
    else {
        node->literal = std::make_shared<Lexer::Token>(eat());
        return node;
    }
}

std::shared_ptr<AST::MulExprNode> Parser::parseMulExpr() {
    if(!isMulExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Literal Or Expression", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::MulExprNode>();
    node->prims.emplace_back(parsePrimExpr());
    while ((peek().content == "*" || peek().content == "/") && peek().type == Lexer::Symbol) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->prims.emplace_back(parsePrimExpr());
    }

    return node;
}

std::shared_ptr<AST::AddExprNode> Parser::parseAddExpr() {
    if(!isMulExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Literal Or Expression", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::AddExprNode>();
    node->muls.emplace_back(parseMulExpr());
    while ((peek().content == "+" || peek().content == "-") && peek().type == Lexer::Symbol) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->muls.emplace_back(parseMulExpr());
    }

    return node;
}

std::shared_ptr<AST::WholeExprNode> Parser::parseWholeExpr() {
    auto node = std::make_shared<AST::WholeExprNode>();
    
    node->addExpr = parseAddExpr();

    return node;
}


