#include "ast.h"

std::string AST::Node::toString() {
    return "<AST::Node>";
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
    else if (arrayExpr) return arrayExpr->toString();
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

