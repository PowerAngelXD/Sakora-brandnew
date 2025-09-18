#include "visitor.h"

sakora::VMCode sakora::CodeMaker::PUSH(std::string value, std::string arg, int ln, int col) {
    return VMCode(sakora::PUSH, ln, col, {value});
}

sakora::VMCode sakora::CodeMaker::ADD() {
    return VMCode(sakora::ADD, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::SUB() {
    return VMCode(sakora::SUB, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::DIV() {
    return VMCode(sakora::DIV, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::MUL() {
    return VMCode(sakora::MUL, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_EQU() {
    return VMCode(sakora::LGC_EQU, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_AND() {
    return VMCode(sakora::LGC_AND, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_OR() {
    return VMCode(sakora::LGC_OR, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_LS_THAN() {
    return VMCode(sakora::LGC_LS_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_MR_THAN() {
    return VMCode(sakora::LGC_MR_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_LSEQU_THAN() {
    return VMCode(sakora::LGC_LSEQU_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_MREQU_THAN() {
    return VMCode(sakora::LGC_MREQU_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_NOT() {
    return VMCode(sakora::LGC_NOT, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_NOT_EQU() {
    return VMCode(sakora::LGC_NOT_EQU, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::ARR_MAKE(std::string size, int ln, int col) {
    return VMCode(sakora::ARR_MAKE, ln, col, {size});
}

sakora::VMCode sakora::CodeMaker::ARR_TIDY_CHK(int ln, int col) {
    return VMCode(sakora::ARR_TIDY_CHK, ln, col, {});
}

sakora::VMCode sakora::CodeMaker::DECLARE(std::string name, int ln, int col) {
    return VMCode(sakora::DECLARE, ln, col, {name});
}

sakora::VMCode sakora::CodeMaker::ASSIGN(std::string name, int ln, int col) {
    return VMCode(sakora::ASSIGN, ln, col, {name});
}

sakora::VMCode sakora::CodeMaker::GET(std::string name, int ln, int col) {
    return VMCode(sakora::GET, ln, col, {name});
}

sakora::VMCode sakora::CodeMaker::FROM(std::string type, int ln, int col) {
    return VMCode(sakora::FROM, ln, col, {type});
}

sakora::VMCode sakora::CodeMaker::BLOCK_START() {
    return VMCode(sakora::BLOCK_START, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::BLOCK_END() {
    return VMCode(sakora::BLOCK_END, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::FLAG(std::string flag_name) {
    return VMCode(sakora::FLAG, 0, 0, {flag_name});
}

sakora::VMCode sakora::CodeMaker::JTIN() {
    return VMCode(sakora::JTIN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::JTBCK() {
    return VMCode(sakora::JTBCK, 0, 0, {});
}

// Vistor

void sakora::Visitor::make(sakora::VMCode code) {
    seq.push_back(code);
}

void sakora::Visitor::visit(AST::BasicIdentifierNode node) {
    
}

void sakora::Visitor::visit(AST::AtomIdentifierNode node) {

}

void sakora::Visitor::visit(AST::IdentifierExprNode node) {

}

void sakora::Visitor::visit(AST::PrimExprNode node) {
    if (node.prefixOp && node.prefixOp->content == "-") {
        make(CodeMaker::PUSH("0", CodeArgs::Push::VAL, node.prefixOp->line, node.prefixOp->column));
    }

    if (node.wholeExpr)
        visit(*node.wholeExpr);
    else if (node.arrayExpr)
        visit(*node.arrayExpr);
    else if (node.iden) 
        visit(*node.iden);
    else
        make(CodeMaker::PUSH(node.literal->content, CodeArgs::Push::VAL, node.literal->line, node.literal->column));

    if (node.prefixOp && node.prefixOp->content == "-") make(CodeMaker::SUB());
    else if (node.prefixOp && node.prefixOp->content == "!") make(CodeMaker::LGC_NOT());
}

void sakora::Visitor::visit(AST::MulExprNode node) {
    visit(*node.prims.at(0));
    for (auto i = 0; i < node.ops.size(); i ++) {
        visit(*node.prims.at(i + 1));
        if (node.ops.at(i)->content == "*")
            make(CodeMaker::MUL());
        else
            make(CodeMaker::DIV());
    }
}

void sakora::Visitor::visit(AST::AddExprNode node) {
    visit(*node.muls.at(0));
    for (auto i = 0; i < node.ops.size(); i ++) {
        visit(*node.muls.at(i + 1));
        if (node.ops.at(i)->content == "-")
            make(CodeMaker::SUB());
        else
            make(CodeMaker::ADD());
    }
}

void sakora::Visitor::visit(AST::LogicExprNode node) {
    visit(*node.adds.at(0));
    for (auto i = 0; i < node.ops.size(); i ++) {
        visit(*node.adds.at(i + 1));
        if (node.ops.at(i)->content == "==")
            make(CodeMaker::LGC_EQU());
        else if (node.ops.at(i)->content == "!=")
            make(CodeMaker::LGC_NOT_EQU());
        else if (node.ops.at(i)->content == ">")
            make(CodeMaker::LGC_MR_THAN());
        else if (node.ops.at(i)->content == ">=")
            make(CodeMaker::LGC_MREQU_THAN());
        else if (node.ops.at(i)->content == "<")
            make(CodeMaker::LGC_LS_THAN());
        else
            make(CodeMaker::LGC_LSEQU_THAN());
    }
}

void sakora::Visitor::visit(AST::BoolExprNode node) {
    visit(*node.lgcs.at(0));
    for (auto i = 0; i < node.ops.size(); i ++) {
        visit(*node.lgcs.at(i + 1));
        if (node.ops.at(i)->content == "and")
            make(CodeMaker::LGC_AND());
        else
            make(CodeMaker::LGC_OR());
    }
}

void sakora::Visitor::visit(AST::PrimTypeExprNode node) {
    if (node.identifier->content == "int") {
        make(CodeMaker::PUSH(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "float") {
        make(CodeMaker::PUSH(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "string") {
        make(CodeMaker::PUSH(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "bool") {
        make(CodeMaker::PUSH(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "tid") {
        make(CodeMaker::PUSH(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    if (node.identifier->content == "char") {
        make(CodeMaker::PUSH(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
}

void sakora::Visitor::visit(AST::ArrayTypeExprNode node) {
    std::string result;
    result += node.primType->identifier->content;
    for (auto info : node.arrayInfos) {
        result += info->length->content;
    }
    make(CodeMaker::PUSH(result, CodeArgs::Push::TYPE, node.primType->identifier->line, node.primType->identifier->column));
}

void sakora::Visitor::visit(AST::TypeExprNode node) {
    if (node.prim) visit(*node.prim);
    else if (node.array) visit(*node.array);
}

void sakora::Visitor::visit(AST::ArrayExprNode node) {
    int size = 0;
    for (auto e : node.elements) {
        visit(*e);
        size ++;
    }
    make(CodeMaker::ARR_MAKE(std::to_string(size), node.leftArrayModOp->line, node.leftArrayModOp->column));
    make(CodeMaker::ARR_TIDY_CHK(node.leftArrayModOp->line, node.leftArrayModOp->column));
}

void sakora::Visitor::visit(AST::WholeExprNode node) {
    if (node.addExpr) visit(*node.addExpr);
    else if (node.boolExpr) visit(*node.boolExpr);
    else if (node.typeExpr) visit(*node.typeExpr);
}


void sakora::Visitor::visit(AST::LetStmtNode node) {

}

void sakora::Visitor::visit(AST::AssignStmtNode node) {

}

void sakora::Visitor::visit(AST::BlockStmtNode node, bool jmpCond = false) {

}

void sakora::Visitor::visit(AST::IfStmtNode node) {

}

void sakora::Visitor::visit(AST::ElseIfStmtNode node) {

}

void sakora::Visitor::visit(AST::ElseStmtNode node) {

}

void sakora::Visitor::visit(AST::MatchStmtNode node) {

}

void sakora::Visitor::visit(AST::WhileStmtNode node) {

}

void sakora::Visitor::visit(AST::ExprStmtNode node) {

}


void sakora::Visitor::visit(AST::StmtNode node) {

}
