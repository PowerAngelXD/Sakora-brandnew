#ifndef SAKORA_VISITOR_H
#define SAKORA_VISITOR_H

#include "../Frontend/Parser/parser.h"
#include "instruction.h"

namespace sakora {
    using CodeSequence = std::vector<VMCode>;

    class CodeMaker {
    public:
        static VMCode PUSH(std::string value, int ln, int col);
        static VMCode ADD();
        static VMCode SUB();
        static VMCode MUL();
        static VMCode DIV();
        static VMCode LGC_AND();
        static VMCode LGC_OR();
        static VMCode LGC_NOT_EQU();
        static VMCode LGC_EQU();
        static VMCode LGC_MR_THAN();
        static VMCode LGC_LS_THAN();
        static VMCode LGC_MREQU_THAN();
        static VMCode LGC_LSEQU_THAN();
        static VMCode LGC_NOT();
        static VMCode ARR_MAKE(std::string size, int ln, int col);
        static VMCode ARR_TIDY_CHK(int ln, int col);
        static VMCode DECLARE(std::string name, int ln, int col);
        static VMCode ASSIGN(std::string name, int ln, int col);
        static VMCode GET(std::string name, int ln, int col);
        static VMCode FROM(std::string type, int ln, int col);
        static VMCode NEW_SCOPE();
        static VMCode END_SCOPE();
        static VMCode FLAG(std::string flag_name);
        static VMCode JTIN();
        static VMCode JTBCK();
    };

    class Visitor {
    public:
        CodeSequence seq;

        void make(VMCode code);

        /**
     * 生成函数调用相关指令
     * Visit instructions for function call
     */
    void visit(AST::BasicIdentifierNode node, bool pushObj = false);
    /**
     * 生成原子标识符相关指令
     * Visit instructions for atomic identifier
     */
    void visit(AST::AtomIdentifierNode node, bool pushObj = false);
    /**
     * 生成标识符表达式相关指令
     * Visit instructions for identifier expression
     */
    void visit(AST::IdentifierExprNode node, bool pushObj = false);
    /**
     * 生成基本表达式相关指令
     * Visit instructions for primary expression
     */
    void visit(AST::PrimExprNode node);
    /**
     * 生成乘法表达式相关指令
     * Visit instructions for multiplication expression
     */
    void visit(AST::MulExprNode node);
    /**
     * 生成加法表达式相关指令
     * Visit instructions for addition expression
     */
    void visit(AST::AddExprNode node);
    /**
     * 生成逻辑表达式相关指令
     * Visit instructions for logic expression
     */
    void visit(AST::LogicExprNode node);
    /**
     * 生成布尔表达式相关指令
     * Visit instructions for boolean expression
     */
    void visit(AST::BoolExprNode node);
    /**
     * 生成基本类型表达式相关指令
     * Visit instructions for primary type expression
     */
    void visit(AST::PrimTypeExprNode node);
    /**
     * 生成数组类型表达式相关指令
     * Visit instructions for array type expression
     */
    void visit(AST::ArrayTypeExprNode node);
    /**
     * 生成类型表达式相关指令
     * Visit instructions for type expression
     */
    void visit(AST::TypeExprNode node);
    /**
     * 生成数组表达式相关指令
     * Visit instructions for array expression
     */
    void visit(AST::ArrayExprNode node);
    /**
     * 生成完整表达式相关指令
     * Visit instructions for whole expression
     */
    void visit(AST::WholeExprNode node);

    // Statement 语句相关 / Statement related
    /**
     * 生成let声明语句相关指令
     * Visit instructions for let statement
     */
    void visit(AST::LetStmtNode node);
    /**
     * 生成赋值语句相关指令
     * Visit instructions for assignment statement
     */
    void visit(AST::AssignStmtNode node);
    /**
     * 生成代码块语句相关指令
     * Visit instructions for block statement
     * @param jmpCond 是否为条件跳转块 / Whether it is a conditional jump block
     */
    void visit(AST::BlockStmtNode node, bool jmpCond = false);
    /**
     * 生成if条件语句相关指令
     * Visit instructions for if statement
     */
    void visit(AST::IfStmtNode node);
    /**
     * 生成else if语句相关指令
     * Visit instructions for else-if statement
     */
    void visit(AST::ElseIfStmtNode node);
    /**
     * 生成else语句相关指令
     * Visit instructions for else statement
     */
    void visit(AST::ElseStmtNode node);
    /**
     * 生成match匹配语句相关指令
     * Visit instructions for match statement
     */
    void visit(AST::MatchStmtNode node);
    /**
     * 生成while循环语句相关指令
     * Visit instructions for while statement
     */
    void visit(AST::WhileStmtNode node);
    /**
     * 生成表达式语句相关指令
     * Visit instructions for expression statement
     */
    void visit(AST::ExprStmtNode node);

    /**
     * 生成通用语句相关指令
     * Visit instructions for general statement
     */
    void visit(AST::StmtNode node);
    };
}

#endif