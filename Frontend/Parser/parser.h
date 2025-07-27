#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

class Parser {
    std::size_t index = 0;
    Lexer::TokenSequence seq;
public:
    Parser(Lexer::TokenSequence s);

    // 仅读取当前index下的token，不进行index+1操作
    Lexer::Token peek();
    // 读取当前index下token之后，index+1
    Lexer::Token eat();
    // 一个方便使用的函数
    std::shared_ptr<Lexer::Token> eatAsPtr();

    // checker
    bool isPrimExpr();
    bool isAddExpr();
    bool isMulExpr();
    bool isWholeExpr();

    // parser
    AST::Node parsePrimExpr();
    AST::Node parseAddExpr();
    AST::Node parseMulExpr();
    AST::Node parseWholeExpr();
};

#endif