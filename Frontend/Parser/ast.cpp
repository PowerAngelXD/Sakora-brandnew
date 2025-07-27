#include "ast.h"

AST::Node::Node(AST::NodeType t) {
    type = t;
}

AST::Node::Node(AST::NodeType t, Lexer::Token c) {
    type = t;
    content = c;
}

std::string AST::nodeToString(Node n) {
    return "[Node: " + n.content.toString() + "]";
}

std::string AST::noneToString(Node n) {
    return "[NoneNode" + std::to_string(n.type) + "]";
}

std::string AST::primExprToString(Node n) {
    if (n.type == AST::WholeExpr) {
        if (n.branchs.at(1).type == AST::AddExpr) {
            return addExprToString(n.branchs.at(1));
        }
        else return nodeToString(n);
    }
    else {
        return nodeToString(n);
    }
}

std::string AST::mulExprToString(Node n) {
    if (n.branchs.at(0).branchs.at(0).type == AST::WholeExpr) {
        // TODO: 尚未完善
        return "[MulExprNode: " + wholeExprToString(n.branchs.at(0).branchs.at(0).branchs.at(1)) + "]";
    }
    else {
        std::string result = "[MulExprNode: " + primExprToString(n.branchs.at(0).branchs.at(0));
        bool hasOp = false;
        for(std::size_t i = 0; i < n.branchs.at(0).branchs.size() - 1; i ++) {
            if (n.branchs.size() == 1) {
                return result + "]";
            }   
            else {
                if(!hasOp) {result += ", ";}
                hasOp = true;
                result += nodeToString(n.branchs.at(1).branchs.at(i)) + ", ";
                if (i == n.branchs.at(1).branchs.size() - 1) {
                    result += primExprToString(n.branchs.at(0).branchs.at(i + 1));
                }
                else {
                    result += primExprToString(n.branchs.at(0).branchs.at(i + 1)) + ", ";
                }
            }
        }
        return result + "]";
    }
}

std::string AST::addExprToString(Node n) {
    std::string result = "[AddExprNode: " + mulExprToString(n.branchs.at(0).branchs.at(0)) + ", ";
    for(std::size_t i = 0; i < n.branchs.at(0).branchs.size() - 1; i ++) {
        result += nodeToString(n.branchs.at(1).branchs.at(i)) + ", ";
        if (i == n.branchs.at(1).branchs.size() - 1) {
            result += mulExprToString(n.branchs.at(0).branchs.at(i + 1));
        }
        else {
            result += mulExprToString(n.branchs.at(0).branchs.at(i + 1)) + ", ";
        }
    }
    return result + "]";
}

std::string AST::wholeExprToString(Node n) {
    return addExprToString(n);
}