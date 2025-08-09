#include "parser.h"

Parser::Parser(Lexer::TokenSequence s) {
    seq = s;
}

const Lexer::Token& Parser::peek(int offset)
{
    return seq.at(index + offset);
}

const Lexer::Token& Parser::eat() {
    return seq.at(index ++);
}


// 目前的表达式仅支持数字计算
bool Parser::isPrimExpr() {
    return peek().content == "!" || peek().content == "-" || peek().type == Lexer::Number || peek().type == Lexer::String || peek().content == "(" || peek().content == "true" || peek().content == "false";
}

bool Parser::isAddExpr() {
    return isPrimExpr();
}

bool Parser::isMulExpr() {
    return isAddExpr();
}

bool Parser::isLogicExpr() {
    if (peek().content == "true" || peek().content == "false" || peek().content == "!") return true;
    if (isAddExpr()) {
        if (peek().content == "(" && (
            peek(2).content == "==" || peek(2).content == "!=" || peek(2).content == ">=" || peek(2).content == "<=" || peek(2).content == ">" || peek(2).content == "<"
            )) return true;

        if (peek(1).content == "==" || peek(1).content == "!=" || peek(1).content == ">=" || peek(1).content == "<=" || peek(1).content == ">" || peek(1).content == "<") return true;
        else return false;
    }
    else return false;
}

bool Parser::isBoolExpr() {
    return isLogicExpr();
}

bool Parser::isPrimTypeExpr() {
    return peek().type == Lexer::Keyword || peek().type == Lexer::Identifier;
}

bool Parser::isArrayTypeExpr() {
    if (isPrimTypeExpr()) {
        if (peek(1).content == "[") return true;
        else return false;
    }
    else return false;
}

bool Parser::isTypeExpr() {
    return isPrimTypeExpr() || isArrayTypeExpr();
}


bool Parser::isWholeExpr() {
    return isAddExpr() || isBoolExpr();
}

std::shared_ptr<AST::PrimExprNode> Parser::parsePrimExpr() {
    if (!isPrimExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Literal Or Expression", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::PrimExprNode>();
    if (peek().content == "!" || peek().content == "-") {
        node->prefixOp = std::make_shared<Lexer::Token>(eat());
    }

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

std::shared_ptr<AST::LogicExprNode> Parser::parseLogicExpr() {
    if (!isLogicExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Logic Operator", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::LogicExprNode>();
    node->adds.emplace_back(parseAddExpr());
    while ((peek().content == "==" || peek().content == "!=" || peek().content == ">=" || peek().content == "<=" || peek().content == ">" || peek().content == "<") && peek().type == Lexer::Symbol) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->adds.emplace_back(parseAddExpr());
    }

    return node;
}

std::shared_ptr<AST::BoolExprNode> Parser::parseBoolExpr() {
    if (!isBoolExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Boolean Operator", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::BoolExprNode>();
    node->lgcs.emplace_back(parseLogicExpr());
    while ((peek().content == "and" || peek().content == "or") && peek().type == Lexer::Keyword) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->lgcs.emplace_back(parseLogicExpr());
    }

    return node;
}

std::shared_ptr<AST::PrimTypeExprNode> Parser::parsePrimTypeExpr() {
    if (!isPrimTypeExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Type Identifier", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::PrimTypeExprNode>();
    node->identifier = std::make_shared<Lexer::Token>(eat());

    return node;
}

std::shared_ptr<AST::ArrayTypeExprNode> Parser::parseArrayTypeExpr() {
    if (!isArrayTypeExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Type Identifier And ArraySymbol", peek().line, peek().column);
    }
    auto node = std::make_shared<AST::ArrayTypeExprNode>();

    node->primType = parsePrimTypeExpr();
    
    while (peek().content == "[") {
        auto info = std::make_shared<AST::ArrayTypeExprNode::ArrayInfoOpNode>();
        info->leftArrayModOp = std::make_shared<Lexer::Token>(eat());
        if (peek().type != Lexer::Number) {
            throw ParserError::WrongMatchError(peek().content, "Number", peek().line, peek().column);
        }
        info->length = std::make_shared<Lexer::Token>(eat());
        if (peek().content != "]") {
            throw ParserError::WrongMatchError(peek().content, "']'", peek().line, peek().column);
        }
        info->rightArrayModOp = std::make_shared<Lexer::Token>(eat());
    }

    return node;
}

std::shared_ptr<AST::TypeExprNode> Parser::parseTypeExpr() {
    auto node = std::make_shared<AST::TypeExprNode>();
    
    if (isArrayTypeExpr()) node->array = parseArrayTypeExpr();
    else node->prim = parsePrimTypeExpr();

    return node;
}


std::shared_ptr<AST::WholeExprNode> Parser::parseWholeExpr() {
    auto node = std::make_shared<AST::WholeExprNode>();
    
    if (isBoolExpr()) node->boolExpr = parseBoolExpr();
    else node->addExpr = parseAddExpr();

    return node;
}


