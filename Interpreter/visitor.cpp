#include "visitor.h"
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
        make(CodeMaker::push("0", CodeArgs::Push::VAL, node.prefixOp->line, node.prefixOp->column));
    }

    if (node.wholeExpr)
        visit(*node.wholeExpr);
    else if (node.arrayExpr)
        visit(*node.arrayExpr);
    else if (node.iden) 
        visit(*node.iden);
    else
        make(CodeMaker::push(node.literal->content, CodeArgs::Push::VAL, node.literal->line, node.literal->column));

    if (node.prefixOp && node.prefixOp->content == "-") make(CodeMaker::sub());
    else if (node.prefixOp && node.prefixOp->content == "!") make(CodeMaker::lgcNot());
}

void sakora::Visitor::visit(AST::MulExprNode node) {
    visit(*node.prims.at(0));
    for (std::size_t i = 0; i < node.ops.size(); i ++) {
        visit(*node.prims.at(i + 1));
        if (node.ops.at(i)->content == "*")
            MUL
        else
            DIV
    }
}

void sakora::Visitor::visit(AST::AddExprNode node) {
    visit(*node.muls.at(0));
    for (std::size_t i = 0; i < node.ops.size(); i ++) {
        visit(*node.muls.at(i + 1));
        if (node.ops.at(i)->content == "-")
            SUB
        else
            ADD
    }
}

void sakora::Visitor::visit(AST::LogicExprNode node) {
    visit(*node.adds.at(0));
    for (std::size_t i = 0; i < node.ops.size(); i ++) {
        visit(*node.adds.at(i + 1));
        if (node.ops.at(i)->content == "==")
            LGC_EQU
        else if (node.ops.at(i)->content == "!=")
            LGC_NOT_EQU
        else if (node.ops.at(i)->content == ">")
            LGC_MR_THAN
        else if (node.ops.at(i)->content == ">=")
            LGC_MREQU_THAN
        else if (node.ops.at(i)->content == "<")
            LGC_LS_THAN
        else
            LGC_LSEQU_THAN
    }
}

void sakora::Visitor::visit(AST::BoolExprNode node) {
    visit(*node.lgcs.at(0));
    for (std::size_t i = 0; i < node.ops.size(); i ++) {
        visit(*node.lgcs.at(i + 1));
        if (node.ops.at(i)->content == "and")
            LGC_AND
        else
            LGC_OR
    }
}

void sakora::Visitor::visit(AST::PrimTypeExprNode node) {
    if (node.identifier->content == "int") {
        make(CodeMaker::push(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "float") {
        make(CodeMaker::push(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "string") {
        make(CodeMaker::push(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "bool") {
        make(CodeMaker::push(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    else if (node.identifier->content == "tid") {
        make(CodeMaker::push(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
    if (node.identifier->content == "char") {
        make(CodeMaker::push(node.identifier->content, CodeArgs::Push::TYPE, node.identifier->line, node.identifier->column));
    }
}

void sakora::Visitor::visit(AST::ArrayTypeExprNode node) {
    std::string result;
    result += node.primType->identifier->content;
    for (auto info : node.arrayInfos) {
        result += info->length->content;
    }
    make(CodeMaker::push(result, CodeArgs::Push::TYPE, node.primType->identifier->line, node.primType->identifier->column));
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
    make(CodeMaker::arrMake(std::to_string(size), node.leftArrayModOp->line, node.leftArrayModOp->column));
    make(CodeMaker::arrTidyChk(node.leftArrayModOp->line, node.leftArrayModOp->column));
}

void sakora::Visitor::visit(AST::WholeExprNode node) {
    if (node.addExpr) visit(*node.addExpr);
    else if (node.boolExpr) visit(*node.boolExpr);
    else if (node.typeExpr) visit(*node.typeExpr);
}

// Stmt

void sakora::Visitor::visit(AST::LetStmtNode node) {
    if (node.expr) visit(*node.expr);
    if (node.typeModOp) {
        visit(*node.type);
        make(CodeMaker::declare(node.identifier->content, CodeArgs::Declare::HAS_TMOD, node.letMark->line, node.letMark->column));
    }
    else {
        make(CodeMaker::declare(node.identifier->content, CodeArgs::Declare::NO_TMOD, node.letMark->line, node.letMark->column));
    }
}

void sakora::Visitor::visit(AST::AssignStmtNode node) {
    visit(*node.expr);
    visit(*node.iden);
    make(CodeMaker::assign(node.assignOp->line, node.assignOp->column));
}

void sakora::Visitor::visit(AST::BlockStmtNode node, bool jmpCond = false) {
    BLK_START
        for (auto stmt : node.body) {
            visit(*stmt);
        }
        if (jmpCond) 
            make(CodeMaker::push("true", CodeArgs::Push::VAL, node.rightBrace->line, node.rightBrace->column));
    BLK_END
}

void sakora::Visitor::visit(AST::IfStmtNode node) {
    visit(*node.condition);
    JMPTIN
    visit(*node.bodyBlock, true);
    LGC_NOT

    if (node.elseStmt) {
        visit(*node.elseStmt);
    }
}


void sakora::Visitor::visit(AST::ElseStmtNode node) {
    JMPTIN
    BLK_START
        if (node.bodyBlock) {
            visit(*node.bodyBlock);
        }
        else {
            visit(*node.stmt);
        }
    BLK_END
}

void sakora::Visitor::visit(AST::MatchStmtNode node) {
    int count = 1;
    for (auto block : node.matchBlocks) {
        visit(*node.identifier);
        visit(*block->caseExpr);
        LGC_EQU
        JMPTIN
        visit(*block->bodyBlock, true);
        LGC_NOT
        JMPTIN
        BLK_START
        count ++;
    }

    for (int i = 0; i < count; i ++) {
        BLK_END
    }
}

void sakora::Visitor::visit(AST::WhileStmtNode node) {
    BLK_START
        BLK_START
            visit(*node.condition);
            JMPTIN
            visit(*node.bodyBlock, true);
        BLK_END
        JMPTBCK
    BLK_END
}

void sakora::Visitor::visit(AST::ExprStmtNode node) {
    visit(*node.idenExpr);
}


void sakora::Visitor::visit(AST::StmtNode node) {
    if (node.assignStmt) visit(*node.assignStmt);
    else if (node.letStmt) visit(*node.letStmt);
    else if (node.ifStmt) visit(*node.ifStmt);
    else if (node.matchStmt) visit(*node.matchStmt);
    else if (node.whileStmt) visit(*node.whileStmt);
    else if (node.blockStmt) visit(*node.blockStmt);
    else if (node.exprStmt) visit(*node.exprStmt);
}
