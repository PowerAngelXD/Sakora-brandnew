#include "ast.h"

std::string AST::Node::toString() {
    return "<AST::Node>";
}

std::string AST::CallingExprNode::toString() {
    std::ostringstream oss;
    oss << "<CallingExprNode: ";
    if (iden) oss << iden->content;
    if (left) oss << left->content;
    for (size_t i = 0; i < args.size(); ++i) {
        if (i > 0) oss << ", ";
        if (args[i]) oss << args[i]->toString();
    }
    if (right) oss << right->content;
    oss << ">";
    return oss.str();
}

std::string AST::AtomIdentifierNode::toString() {
    std::ostringstream oss;
    oss << "<AtomIdentifierNode: ";
    if (iden) oss << iden->toString();
    
    for (size_t i = 0; i < getIndexOps.size(); ++i) {
        if (i > 0 && i-1 < getIndexOps.size() && getIndexOps[i-1]) {
            oss << " " << getIndexOps[i-1]->index->toString() << " ";
        }
        if (getIndexOps[i]) oss << getIndexOps[i]->index->toString();
    }

    oss << ">";
    return oss.str();
}

std::string AST::IdentifierExprNode::toString() {
    std::ostringstream oss;
    oss << "<IdentifierExprNode: ";
    for (size_t i = 0; i < idens.size(); ++i) {
        if (i > 0 && i-1 < getOps.size() && getOps[i-1]) {
            oss << getOps[i-1]->content;
        }
        if (idens[i]) oss << idens[i]->toString();
    }
    oss << ">";
    return oss.str();
}

std::string AST::PrimExprNode::toString() {
    std::string prefix;
    if (prefixOp) {
        if (prefixOp->content == "-") prefix = "-";
        else if (prefixOp->content == "!") prefix = "!";
    }

    if (literal) {
        return prefix + literal->content;
    } else if (wholeExpr) {
        return prefix + "(" + wholeExpr->toString() + ")";
    } else if (arrayExpr) {
        return prefix + "(" + arrayExpr->toString() + ")";
    } else if (iden) {
        return prefix + "(" + iden->toString() + ")";
    }
    return "<PrimExprNode: null>";
}

std::string AST::MulExprNode::toString() {
    std::ostringstream oss;
    oss << "<MulExprNode: ";
    for (size_t i = 0; i < prims.size(); ++i) {
        if (i > 0 && i-1 < ops.size() && ops[i-1]) {
            oss << " " << ops[i-1]->content << " ";
        }
        if (prims[i]) oss << prims[i]->toString();
    }
    oss << ">";
    return oss.str();
}

std::string AST::AddExprNode::toString() {
    std::ostringstream oss;
    oss << "<AddExprNode: ";
    for (size_t i = 0; i < muls.size(); ++i) {
        if (i > 0 && i-1 < ops.size() && ops[i-1]) {
            oss << " " << ops[i-1]->content << " ";
        }
        if (muls[i]) oss << muls[i]->toString();
    }
    oss << ">";
    return oss.str();
}

std::string AST::LogicExprNode::toString() {
    std::ostringstream oss;
    oss << "<LogicExprNode: ";
    for (size_t i = 0; i < adds.size(); ++i) {
        if (i > 0 && i-1 < ops.size() && ops[i-1]) {
            oss << " " << ops[i-1]->content << " ";
        }
        if (adds[i]) oss << adds[i]->toString();
    }
    oss << ">";
    return oss.str();
}

std::string AST::BoolExprNode::toString() {
    std::ostringstream oss;
    oss << "<BoolExprNode: ";
    for (size_t i = 0; i < lgcs.size(); ++i) {
        if (i > 0 && i-1 < ops.size() && ops[i-1]) {
            oss << " " << ops[i-1]->content << " ";
        }
        if (lgcs[i]) oss << lgcs[i]->toString();
    }
    oss << ">";
    return oss.str();
}

std::string AST::ArrayExprNode::toString() {
    std::ostringstream oss;
    oss << "<ArrayExprNode: ";
    if (leftArrayModOp) oss << leftArrayModOp->content;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << elements[i]->toString();
    }
    if (rightArrayModOp) oss << rightArrayModOp->content;
    oss << ">";
    return oss.str();
}

std::string AST::WholeExprNode::toString() {
    if (addExpr) return addExpr->toString();
    else if (boolExpr) return boolExpr->toString();
    else if (typeExpr) return typeExpr->toString();
    return "<WholeExprNode: null>";
}

std::string AST::PrimTypeExprNode::toString() {
    std::ostringstream oss;
    oss << "<PrimTypeExprNode: ";
    if (identifier) oss << identifier->content;
    oss << ">";
    return oss.str();
}

std::string AST::ArrayTypeExprNode::toString() {
    std::ostringstream oss;
    oss << "<ArrayTypeExprNode: ";
    if (primType) {
        oss << primType->toString();
    }
    for (const auto& info : arrayInfos) {
        oss << " [";
        if (info && info->leftArrayModOp) oss << info->leftArrayModOp->content;
        if (info && info->length) oss << info->length->content;
        if (info && info->rightArrayModOp) oss << info->rightArrayModOp->content;
        oss << "]";
    }
    oss << ">";
    return oss.str();
}

std::string AST::TypeExprNode::toString() {
    if (prim) return prim->toString();
    if (array) return array->toString();
    return "<TypeExprNode: null>";
}



// STMT

std::string AST::LetStmtNode::toString() {
    std::ostringstream oss;
    oss << "<LetStmtNode: ";
    oss << letMark->content << " ";
    oss << identifier->content << " ";
    if (typeModOp) oss << typeModOp->content << " ";
    if (typeModOp) oss << type->toString() << " ";
    if (assignOp) oss << assignOp->content << " ";
    if (assignOp) oss << expr->toString() << " ";
    oss << stmtEndOp->content;
    oss << ">";
    return oss.str();
}

std::string AST::AssignStmtNode::toString() {
    std::ostringstream oss;
    oss << "<AssignStmtNode: ";
    oss << iden->toString() << " ";
    oss << assignOp->content << " ";
    oss << expr->toString();
    oss << ">";
    return oss.str();
}

std::string AST::BlockStmtNode::toString() {
    std::ostringstream oss;
    oss << "BlockStmtNode(";
    if (leftBrace) oss << "leftBrace: " << leftBrace->toString() << ", ";
    oss << "body: [";
    for (size_t i = 0; i < body.size(); ++i) {
        if (body[i]) oss << body[i]->toString();
        if (i + 1 < body.size()) oss << ", ";
    }
    oss << "], ";
    if (rightBrace) oss << "rightBrace: " << rightBrace->toString();
    oss << ")";
    return oss.str();
}

std::string AST::IfStmtNode::toString() {
    std::ostringstream oss;
    oss << "IfStmtNode(";
    if (ifMark) oss << "ifMark: " << ifMark->toString() << ", ";
    if (condition) oss << "condition: " << condition->toString() << ", ";
    if (bodyBlock) oss << "bodyBlock: " << bodyBlock->toString() << ", ";
    oss << "elseIfs: [";
    for (size_t i = 0; i < elseIfstmts.size(); ++i) {
        if (elseIfstmts[i]) oss << elseIfstmts[i]->toString();
        if (i + 1 < elseIfstmts.size()) oss << ", ";
    }
    oss << "], ";
    if (elseStmt) oss << "elseStmt: " << elseStmt->toString();
    oss << ")";
    return oss.str();
}

std::string AST::ElseIfStmtNode::toString() {
    std::ostringstream oss;
    oss << "ElseIfStmtNode(";
    if (elseMark) oss << elseMark->toString() << ", ";
    if (ifMark) oss << ifMark->toString() << ", ";
    if (condition) oss << "condition: " << condition->toString() << ", ";
    if (bodyBlock) oss << "bodyBlock: " << bodyBlock->toString();
    oss << ")"; 
    return oss.str();
}

std::string AST::ElseStmtNode::toString() {
    std::ostringstream oss;
    oss << "ElseStmtNode(";
    if (elseMark) oss << "elseMark: " << elseMark->toString() << ", ";
    if (bodyBlock) oss << "bodyBlock: " << bodyBlock->toString();
    oss << ")";
    return oss.str();
}

std::string AST::MatchStmtNode::toString() {
    std::ostringstream oss;
    oss << "MatchStmtNode(";
    if (matchMark) oss << "matchMark: " << matchMark->toString() << ", ";
    if (identifier) oss << "iden: " << identifier->toString() << ", ";
    oss << "matchBlocks: [";
    for (size_t i = 0; i < matchBlocks.size(); ++i) {
        const auto& block = matchBlocks[i];
        if (block) {
            oss << "{";
            if (block->caseExpr) oss << "caseExpr: " << block->caseExpr->toString() << ", ";
            if (block->bodyBlock) oss << "bodyBlock: " << block->bodyBlock->toString();
            oss << "}";
        }
        if (i + 1 < matchBlocks.size()) oss << ", ";
    }
    oss << "]";
    if (defaultMark) oss << ", defaultMark: " << defaultMark->toString();
    if (defaultBlock) oss << ", defaultBlock: " << defaultBlock->toString();
    if (rightBrace) oss << ", rightBrace: " << rightBrace->toString();
    oss << ")";
    return oss.str();
}

std::string AST::StmtNode::toString() {
    if (letStmt) return letStmt->toString();
    else if (ifStmt) return ifStmt->toString();
    else if (elseIfStmt) return elseIfStmt->toString();
    else if (elseStmt) return elseStmt->toString();
    else if (blockStmt) return blockStmt->toString();
    else if (matchStmt) return matchStmt->toString();
    else return assignStmt->toString();
}

