#include "parser.h"

Parser::Parser(Lexer::TokenSequence s) {
    seq = s;
}

Lexer::Token Parser::peek(int offset)
{
    return seq.at(index + offset);
}

Lexer::Token Parser::eat() {
    return seq.at(index ++);
}


// 目前的表达式仅支持数字计算
bool Parser::isPrimExpr() {
    return peek().type == Lexer::Number || peek().type == Lexer::String || peek().content == "(";
}

bool Parser::isAddExpr() {
    return isPrimExpr();
}

bool Parser::isMulExpr() {
    return isAddExpr();
}

bool Parser::isBoolExpr() {
    if (peek().content == "true" || peek().content == "false") return true;
    if (isAddExpr()) {
        if (peek(1).content == "and" || peek(1).content == "or") return true;
        else return false;
    }
    else return false;
}

bool Parser::isWholeExpr() {
    return isAddExpr() || isBoolExpr();
}

std::shared_ptr<AST::PrimExprNode> Parser::parsePrimExpr() {
    if (!isPrimExpr()) {
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
    if (!isMulExpr()) {
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
    if (!isMulExpr()) {
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

std::shared_ptr<AST::BoolExprNode> Parser::parseBoolExpr() {
    if (!isBoolExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Boolean Operator", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::BoolExprNode>();
    node->adds.emplace_back(parseAddExpr());
    while ((peek().content == "and" || peek().content == "or") && peek().type == Lexer::Keyword) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->adds.emplace_back(parseAddExpr());
    }

    return node;
}

std::shared_ptr<AST::WholeExprNode> Parser::parseWholeExpr() {
    auto node = std::make_shared<AST::WholeExprNode>();
    
    if (isBoolExpr()) node->boolExpr = parseBoolExpr();
    else node->addExpr = parseAddExpr();

    return node;
}


