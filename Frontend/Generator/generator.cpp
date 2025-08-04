#include "generator.h"

void Generator::generate(AST::PrimExprNode node) {
    if(node.wholeExpr) {
        generate(*node.wholeExpr);
    }
    else {
        if (node.literal->type == Lexer::Number) {
            if (node.literal->content.find('.') != std::string::npos) {
                insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {sakValue::createFloatVal(node.literal->content, node.literal->line, node.literal->column)}));
            }
            else {
                insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {sakValue::createIntVal(node.literal->content, node.literal->line, node.literal->column)}));
            }
        }
        else if (node.literal->type == Lexer::String) {
            insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {sakValue::createStringVal(node.literal->content, node.literal->line, node.literal->column)}));
        }
        else if (node.literal->type == Lexer::Keyword && (node.literal->content == "true" || node.literal->content == "false")) {
            insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {sakValue::createBoolVal(node.literal->content, node.literal->line, node.literal->column)}));
        }
    }
}

void Generator::generate(AST::MulExprNode node) {
    generate(*node.prims.at(0));
    for(std::size_t i = 0; i < node.ops.size(); i ++) {
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
    for(std::size_t i = 0; i < node.ops.size(); i ++) {
        generate(*node.muls.at(i + 1));
        if (node.ops.at(i)->content == "+") {
            insSet.emplace_back(INS::genIns(INS::ADD, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else {
            insSet.emplace_back(INS::genIns(INS::SUB, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
    }
}

void Generator::generate(AST::BoolExprNode node) {
    generate(*node.adds.at(0));
    for(std::size_t i = 0; i < node.ops.size(); i ++) {
        generate(*node.adds.at(i + 1));
        if (node.ops.at(i)->content == "and") {
            insSet.emplace_back(INS::genIns(INS::LGC_AND, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else {
            insSet.emplace_back(INS::genIns(INS::LGC_OR, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
    }
}

void Generator::generate(AST::WholeExprNode node) {
    if (node.addExpr) {
        generate(*node.addExpr);
    }
    else if (node.boolExpr) {
        generate(*node.boolExpr);
    }
}
