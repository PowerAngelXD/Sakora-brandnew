#ifndef SAKORA_PARSER_H
#define SAKORA_PARSER_H

#include "ast.h"
#include "../../Error/ParserError.h"

/**
 * Parser类 - 语法解析器
 * Parser class - Syntax parser
 */
class Parser {
    // 当前处理的token索引 / Current token index being processed
    std::size_t index = 0;
    // token序列 / Sequence of tokens
    Lexer::TokenSequence seq;
public:
    // 构造函数，接收token序列 / Constructor that takes a token sequence
    Parser(Lexer::TokenSequence s);

    /**
     * 查看当前token但不消费
     * Peek at current token without consuming it
     * @param offset 偏移量 / Offset from current position
     */
    const Lexer::Token& peek(int offset = 0);

    /**
     * 消费并返回当前token
     * Consume and return current token
     */
    const Lexer::Token& eat();

    // Expression 表达式相关 / Expression related
    // 检查器 / Checkers
    bool isCallingExpr();     // 函数调用表达式检查 / Function call expression check
    bool isAtomIdentifier();  // 原子标识符检查 / Atomic identifier check
    bool isIdentifierExpr();  // 标识符表达式检查 / Identifier expression check
    bool isPrimExpr();        // 基本表达式检查 / Primary expression check
    bool isAddExpr();         // 加法表达式检查 / Addition expression check
    bool isMulExpr();         // 乘法表达式检查 / Multiplication expression check
    bool isLogicExpr();       // 逻辑表达式检查 / Logic expression check
    bool isBoolExpr();        // 布尔表达式检查 / Boolean expression check
    bool isPrimTypeExpr();    // 基本类型表达式检查 / Primary type expression check
    bool isArrayTypeExpr();   // 数组类型表达式检查 / Array type expression check
    bool isTypeExpr();        // 类型表达式检查 / Type expression check
    bool isArrayExpr();       // 数组表达式检查 / Array expression check
    bool isWholeExpr();       // 完整表达式检查 / Whole expression check

    // 解析器 / Parsers
    std::shared_ptr<AST::BasicIdentifierNode> parseCallingExpr();     // 解析函数调用 / Parse function call
    std::shared_ptr<AST::AtomIdentifierNode> parseAtomIdentifier();   // 解析原子标识符 / Parse atomic identifier
    std::shared_ptr<AST::IdentifierExprNode> parseIdentifierExpr();   // 解析标识符表达式 / Parse identifier expression
    std::shared_ptr<AST::PrimExprNode> parsePrimExpr();              // 解析基本表达式 / Parse primary expression
    std::shared_ptr<AST::MulExprNode> parseMulExpr();                // 解析乘法表达式 / Parse multiplication expression
    std::shared_ptr<AST::AddExprNode> parseAddExpr();                // 解析加法表达式 / Parse addition expression
    std::shared_ptr<AST::BoolExprNode> parseBoolExpr();              // 解析布尔表达式 / Parse boolean expression
    std::shared_ptr<AST::LogicExprNode> parseLogicExpr();            // 解析逻辑表达式 / Parse logic expression
    std::shared_ptr<AST::PrimTypeExprNode> parsePrimTypeExpr();      // 解析基本类型表达式 / Parse primary type expression
    std::shared_ptr<AST::ArrayTypeExprNode> parseArrayTypeExpr();    // 解析数组类型表达式 / Parse array type expression
    std::shared_ptr<AST::TypeExprNode> parseTypeExpr();              // 解析类型表达式 / Parse type expression
    std::shared_ptr<AST::ArrayExprNode> parseArrayExpr();            // 解析数组表达式 / Parse array expression
    std::shared_ptr<AST::WholeExprNode> parseWholeExpr();            // 解析完整表达式 / Parse whole expression


    // Statement 语句相关 / Statement related
    // 检查器 / Checkers
    bool isLetStmt();         // let声明语句检查 / Let declaration statement check
    bool isAssignStmt();      // 赋值语句检查 / Assignment statement check
    bool isBlockStmt();       // 代码块语句检查 / Block statement check
    bool isIfStmt();          // if条件语句检查 / If statement check
    bool isElseStmt();        // else语句检查 / Else statement check
    bool isMatchStmt();       // match匹配语句检查 / Match statement check
    bool isWhileStmt();       // while循环语句检查 / While statement check
    bool isExprStmt();        // 表达式语句检查 / Expression statement check

    // 解析器 / Parsers
    std::shared_ptr<AST::LetStmtNode> parseLetStmt();                // 解析let声明语句 / Parse let declaration
    std::shared_ptr<AST::AssignStmtNode> parseAssignStmt();         // 解析赋值语句 / Parse assignment statement
    std::shared_ptr<AST::BlockStmtNode> parseBlockStmt();           // 解析代码块语句 / Parse block statement
    std::shared_ptr<AST::IfStmtNode> parseIfStmt();                 // 解析if条件语句 / Parse if statement
    std::shared_ptr<AST::ElseStmtNode> parseElseStmt();            // 解析else语句 / Parse else statement
    std::shared_ptr<AST::MatchStmtNode> parseMatchStmt();          // 解析match匹配语句 / Parse match statement
    std::shared_ptr<AST::WhileStmtNode> parseWhileStmt();          // 解析while循环语句 / Parse while statement
    std::shared_ptr<AST::ExprStmtNode> parseExprStmt();            // 解析表达式语句 / Parse expression statement
    

    // 最终解析器 / Final Parser
    /**
     * 检查是否为有效语句
     * Check if current token sequence forms a valid statement
     */
    bool isStmt();

    /**
     * 解析单条语句
     * Parse a single statement
     */
    std::shared_ptr<AST::StmtNode> parseStmt();

    /**
     * 解析整个程序
     * Parse the entire program
     * @return 语句节点向量 / Vector of statement nodes
     */
    std::vector<std::shared_ptr<AST::StmtNode>> parse();
};

#endif