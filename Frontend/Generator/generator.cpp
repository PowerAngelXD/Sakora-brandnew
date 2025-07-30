#include "generator.h"

void Generator::generate(AST::PrimExprNode node) {
    if(node.wholeExpr) {
        generate(*node.wholeExpr);
    }
    else {
        if(node.literal->content.find('.')) {
            insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {atof(node.literal->content.c_str())}));
        }
        else {
            insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {atoi(node.literal->content.c_str())}));
        }
    }
}

void Generator::generate(AST::MulExprNode node) {
    generate(*node.prims.at(0));
    for(std::size_t i = 0; i < node.ops.size() - 1; i ++) {
        generate(*node.prims.at(i + 1));
        if (node.ops.at(i)->content == "*") {
            insSet.emplace_back(INS::genIns(INS::MUL, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else {
            insSet.emplace_back(INS::genIns(INS::DIV, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
    }
}

void Generator::generate(AST::AddExprNode node) {
    generate(*node.muls.at(0));
    for(std::size_t i = 0; i < node.ops.size() - 1; i ++) {
        generate(*node.muls.at(i + 1));
        if (node.ops.at(i)->content == "+") {
            insSet.emplace_back(INS::genIns(INS::ADD, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else {
            insSet.emplace_back(INS::genIns(INS::SUB, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
    }
}

void Generator::generate(AST::WholeExprNode node) {
    if (node.addExpr) {
        generate(*node.addExpr);
    }
}
