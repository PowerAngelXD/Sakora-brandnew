#ifndef SAKORA_GENERATOR_H
#define GENERATOR_H

#include "../Parser/parser.h"
#include "../../Backend/ins.h"

/**
 * Generator类 - 代码生成器
 * Generator class - Code generator
 * 负责将AST节点转换为指令集
 * Responsible for converting AST nodes to instruction set
 */
class Generator {
public:
    // 指令集合 / Instruction set
    std::vector<INS::Instruction> insSet;

    /**
     * 生成函数调用相关指令
     * Generate instructions for function call
     */
    void generate(AST::BasicIdentifierNode node, bool pushObj = false);
    /**
     * 生成原子标识符相关指令
     * Generate instructions for atomic identifier
     */
    void generate(AST::AtomIdentifierNode node, bool pushObj = false);
    /**
     * 生成标识符表达式相关指令
     * Generate instructions for identifier expression
     */
    void generate(AST::IdentifierExprNode node, bool pushObj = false);
    /**
     * 生成基本表达式相关指令
     * Generate instructions for primary expression
     */
    void generate(AST::PrimExprNode node);
    /**
     * 生成乘法表达式相关指令
     * Generate instructions for multiplication expression
     */
    void generate(AST::MulExprNode node);
    /**
     * 生成加法表达式相关指令
     * Generate instructions for addition expression
     */
    void generate(AST::AddExprNode node);
    /**
     * 生成逻辑表达式相关指令
     * Generate instructions for logic expression
     */
    void generate(AST::LogicExprNode node);
    /**
     * 生成布尔表达式相关指令
     * Generate instructions for boolean expression
     */
    void generate(AST::BoolExprNode node);
    /**
     * 生成基本类型表达式相关指令
     * Generate instructions for primary type expression
     */
    void generate(AST::PrimTypeExprNode node);
    /**
     * 生成数组类型表达式相关指令
     * Generate instructions for array type expression
     */
    void generate(AST::ArrayTypeExprNode node);
    /**
     * 生成类型表达式相关指令
     * Generate instructions for type expression
     */
    void generate(AST::TypeExprNode node);
    /**
     * 生成数组表达式相关指令
     * Generate instructions for array expression
     */
    void generate(AST::ArrayExprNode node);
    /**
     * 生成完整表达式相关指令
     * Generate instructions for whole expression
     */
    void generate(AST::WholeExprNode node);

    // Statement 语句相关 / Statement related
    /**
     * 生成let声明语句相关指令
     * Generate instructions for let statement
     */
    void generate(AST::LetStmtNode node);
    /**
     * 生成赋值语句相关指令
     * Generate instructions for assignment statement
     */
    void generate(AST::AssignStmtNode node);
    /**
     * 生成代码块语句相关指令
     * Generate instructions for block statement
     * @param jmpCond 是否为条件跳转块 / Whether it is a conditional jump block
     */
    void generate(AST::BlockStmtNode node, bool jmpCond = false);
    /**
     * 生成if条件语句相关指令
     * Generate instructions for if statement
     */
    void generate(AST::IfStmtNode node);
    /**
     * 生成else语句相关指令
     * Generate instructions for else statement
     */
    void generate(AST::ElseStmtNode node);
    /**
     * 生成match匹配语句相关指令
     * Generate instructions for match statement
     */
    void generate(AST::MatchStmtNode node);
    /**
     * 生成while循环语句相关指令
     * Generate instructions for while statement
     */
    void generate(AST::WhileStmtNode node);
    /**
     * 生成表达式语句相关指令
     * Generate instructions for expression statement
     */
    void generate(AST::ExprStmtNode node);

    /**
     * 生成通用语句相关指令
     * Generate instructions for general statement
     */
    void generate(AST::StmtNode node);
};

#endif