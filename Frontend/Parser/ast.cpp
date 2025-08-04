#include "ast.h"
#include <sstream>

std::string AST::Node::toString() {
    return "<AST::Node>";
}

std::string AST::PrimExprNode::toString() {
    if (literal) {
        return literal->content;
    } else if (wholeExpr) {
        return "(" + wholeExpr->toString() + ")";
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

std::string AST::BoolExprNode::toString() {
    std::ostringstream oss;
    oss << "<BoolExprNode: ";
    for (size_t i = 0; i < adds.size(); ++i) {
        if (i > 0 && i-1 < ops.size() && ops[i-1]) {
            oss << " " << ops[i-1]->content << " ";
        }
        if (adds[i]) oss << adds[i]->toString();
    }
    oss << ">";
    return oss.str();
}

std::string AST::WholeExprNode::toString() {
    if (addExpr) return addExpr->toString();
    return "<WholeExprNode: null>";
}

