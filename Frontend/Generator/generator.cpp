#include "generator.h"
#include <string>

void Generator::generate(AST::PrimExprNode node) {
    if (node.prefixOp && node.prefixOp->content == "-") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {sakValue::createIntVal("0", node.literal->line, node.literal->column)}));
    }

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

    if (node.prefixOp && node.prefixOp->content == "-") {
        insSet.emplace_back(INS::genIns(INS::SUB, node.literal->line, node.literal->column, {}));
    }
    else if (node.prefixOp && node.prefixOp->content == "!") {
        insSet.emplace_back(INS::genIns(INS::LGC_NOT, node.prefixOp->line, node.prefixOp->column, {}));
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

void Generator::generate(AST::LogicExprNode node) {
    generate(*node.adds.at(0));
    for(std::size_t i = 0; i < node.ops.size(); i ++) {
        generate(*node.adds.at(i + 1));
        if (node.ops.at(i)->content == "==") {
            insSet.emplace_back(INS::genIns(INS::LGC_EQU, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else if (node.ops.at(i)->content == "!=") {
            insSet.emplace_back(INS::genIns(INS::LGC_NOT_EQU, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else if (node.ops.at(i)->content == ">=") {
            insSet.emplace_back(INS::genIns(INS::LGC_MREQU_THAN, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else if (node.ops.at(i)->content == "<=") {
            insSet.emplace_back(INS::genIns(INS::LGC_LSEQU_THAN, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else if (node.ops.at(i)->content == ">") {
            insSet.emplace_back(INS::genIns(INS::LGC_MR_THAN, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else if (node.ops.at(i)->content == "<") {
            insSet.emplace_back(INS::genIns(INS::LGC_LS_THAN, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
    }
}

void Generator::generate(AST::BoolExprNode node) {
    generate(*node.lgcs.at(0));
    for(std::size_t i = 0; i < node.ops.size(); i ++) {
        generate(*node.lgcs.at(i + 1));
        if (node.ops.at(i)->content == "and") {
            insSet.emplace_back(INS::genIns(INS::LGC_AND, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
        else {
            insSet.emplace_back(INS::genIns(INS::LGC_OR, node.ops.at(i)->line, node.ops.at(i)->column, {}));
        }
    }
}

void Generator::generate(AST::PrimTypeExprNode node) {
    if (node.identifier->content == "int") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.identifier->line, node.identifier->column, 
                        {sakValue(sakType::sakTid(sakType::Type::Int), node.identifier->line, node.identifier->column)}));
    }
    else if (node.identifier->content == "float") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.identifier->line, node.identifier->column, 
                        {sakValue(sakType::sakTid(sakType::Type::Float), node.identifier->line, node.identifier->column)}));
    }
    else if (node.identifier->content == "string") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.identifier->line, node.identifier->column, 
                        {sakValue(sakType::sakTid(sakType::Type::String), node.identifier->line, node.identifier->column)}));
    }
    else if (node.identifier->content == "bool") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.identifier->line, node.identifier->column, 
                        {sakValue(sakType::sakTid(sakType::Type::Boolean), node.identifier->line, node.identifier->column)}));
    }
    else if (node.identifier->content == "tid") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.identifier->line, node.identifier->column, 
                        {sakValue(sakType::sakTid(sakType::Type::Tid), node.identifier->line, node.identifier->column)}));
    }
    else {
        // TODO: 对于其他类型的处理
    }
}

void Generator::generate(AST::ArrayTypeExprNode node) {
    sakType::ArrayModifider amr;
    if (node.primType->identifier->content == "int") {
        amr.arrayType = sakType::Type::Int;
    }
    else if (node.primType->identifier->content == "float") {
        amr.arrayType = sakType::Type::Float;
    }
    else if (node.primType->identifier->content == "string") {
        amr.arrayType = sakType::Type::String;
    }   
    else if (node.primType->identifier->content == "bool") {
        amr.arrayType = sakType::Type::Boolean;
    }
    else if (node.primType->identifier->content == "tid") {
        amr.arrayType = sakType::Type::Tid;
    }

    for (auto info : node.arrayInfos) {
        amr.dimension += 1;
        amr.lengths.emplace_back(std::stoi(info->length->content.c_str()));
    }
    insSet.emplace_back(INS::genIns(INS::PUSH, node.primType->identifier->line, node.primType->identifier->column, 
                        {sakValue(sakType::sakTid(sakType::Type::EMPTY, amr), node.primType->identifier->line, node.primType->identifier->column)}));
}

void Generator::generate(AST::TypeExprNode node) {
    if (node.prim) generate(*node.prim);
    else if (node.array) generate(*node.array);
}

void Generator::generate(AST::ArrayExprNode node) {
    for (auto element : node.elements) {
        generate(*element);
    }
    insSet.emplace_back(INS::genIns(INS::MAKE_ARR, node.leftArrayModOp->line, node.leftArrayModOp->column, 
                        {sakValue::createIntVal(std::to_string(node.elements.size()), node.leftArrayModOp->line, node.leftArrayModOp->column)}));
    insSet.emplace_back(INS::genIns(INS::CHK_CONST_ARR, node.leftArrayModOp->line, node.leftArrayModOp->column, {}));
}


void Generator::generate(AST::WholeExprNode node) {
    if (node.addExpr) {
        generate(*node.addExpr);
    }
    else if (node.boolExpr) {
        generate(*node.boolExpr);
    }
    else if (node.arrayExpr) {
        generate(*node.arrayExpr);
    }
}
