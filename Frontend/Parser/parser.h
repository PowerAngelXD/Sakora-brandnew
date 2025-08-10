#ifndef SAKORA_PARSER_H
#define SAKORA_PARSER_H

#include "ast.h"
#include "../../Error/ParserError.h"

class Parser {
    std::size_t index = 0;
    Lexer::TokenSequence seq;
public:
    Parser(Lexer::TokenSequence s);

    // 仅读取当前index下的token，不进行index+1操作
    const Lexer::Token& peek(int offset = 0);
    // 读取当前index下token之后，index+1
    const Lexer::Token& eat();

    // checker
    bool isPrimExpr();
    bool isAddExpr();
    bool isMulExpr();
    bool isLogicExpr();
    bool isBoolExpr();
    bool isPrimTypeExpr();
    bool isArrayTypeExpr();
    bool isTypeExpr();
    bool isArrayExpr();
    bool isWholeExpr();

    // parser
    std::shared_ptr<AST::PrimExprNode> parsePrimExpr();
    std::shared_ptr<AST::MulExprNode> parseMulExpr();
    std::shared_ptr<AST::AddExprNode> parseAddExpr();
    std::shared_ptr<AST::BoolExprNode> parseBoolExpr();
    std::shared_ptr<AST::LogicExprNode> parseLogicExpr();
    std::shared_ptr<AST::PrimTypeExprNode> parsePrimTypeExpr();
    std::shared_ptr<AST::ArrayTypeExprNode> parseArrayTypeExpr();
    std::shared_ptr<AST::TypeExprNode> parseTypeExpr();
    std::shared_ptr<AST::ArrayExprNode> parseArrayExpr();
    std::shared_ptr<AST::WholeExprNode> parseWholeExpr();
    
};

#endif