#include "generator.h"
#include <string>

void Generator::generate(AST::AtomIdentifierNode node, bool pushObj) {
    auto id = node.iden->iden;

    if (!pushObj)
        insSet.emplace_back(INS::genIns(INS::GET_VAL, id->line, id->column, {sakValue::createStringVal(id->content, id->line, id->column)}));
    else 
        insSet.emplace_back(INS::genIns(INS::PUSH_OBJ, id->line, id->column, {sakValue::createStringVal(id->content, id->line, id->column)}));


    if (!node.getIndexOps.empty()) {
        for (auto indexOp : node.getIndexOps) {
            generate(*indexOp->index);

            insSet.emplace_back(INS::genIns(INS::FROM, indexOp->left->line, indexOp->left->column, {sakValue::createStringVal("[Index]", indexOp->left->line, indexOp->left->column)}));
        }
    }
}

void Generator::generate(AST::IdentifierExprNode node) {
    generate(*node.idens.at(0));
    for (std::size_t i = 1; i < node.getOps.size(); i ++) {
        generate(*node.idens.at(i));
        insSet.emplace_back(INS::genIns(INS::FROM, node.getOps.at(i)->line, node.getOps.at(i)->column, {sakValue::createStringVal("[Member]", node.getOps.at(i)->line,node.getOps.at(i)->column)}));
    }
}

void Generator::generate(AST::PrimExprNode node) {
    if (node.prefixOp && node.prefixOp->content == "-") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {sakValue::createIntVal("0", node.literal->line, node.literal->column)}));
    }

    if(node.wholeExpr) {
        generate(*node.wholeExpr);
    }
    else if (node.arrayExpr) {
        generate(*node.arrayExpr);
    }
    else if (node.iden) {
        if (node.iden->idens.at(0)->iden->iden) {
            // TODO: 没有函数，结构体之前先这样简单处理一下，之后要做完整的generate函数
            generate(*node.iden->idens.at(0));
        }
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
        else if (node.literal->type == Lexer::Char) {
            insSet.emplace_back(INS::genIns(INS::PUSH, node.literal->line, node.literal->column, {sakValue::createCharVal(node.literal->content, node.literal->line, node.literal->column)}));
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
    else if (node.identifier->content == "char") {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.identifier->line, node.identifier->column, 
                        {sakValue(sakType::sakTid(sakType::Type::Char), node.identifier->line, node.identifier->column)}));
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
    insSet.emplace_back(INS::genIns(INS::ARR_MAKE, node.leftArrayModOp->line, node.leftArrayModOp->column, 
                        {sakValue::createIntVal(std::to_string(node.elements.size()), node.leftArrayModOp->line, node.leftArrayModOp->column)}));
    insSet.emplace_back(INS::genIns(INS::ARR_TIDY_CHK, node.leftArrayModOp->line, node.leftArrayModOp->column, {}));
}


void Generator::generate(AST::WholeExprNode node) {
    if (node.addExpr) {
        generate(*node.addExpr);
    }
    else if (node.typeExpr) {
        generate(*node.typeExpr);
    }
    else if (node.boolExpr) {
        generate(*node.boolExpr);
    }
}




void Generator::generate(AST::LetStmtNode node) {
    if (node.expr) generate(*node.expr);
    // 判断有没有类型约束说明
    if (node.typeModOp) {
        generate(*node.type);
        insSet.emplace_back(INS::genIns(INS::DECLARE, 
                                        node.letMark->line, 
                                        node.letMark->column, 
                                        {sakValue::createStringVal(node.identifier->content, node.identifier->line, node.identifier->column), 
                                        sakValue::createStringVal("[HasTypeModifier]", node.typeModOp->line, node.typeModOp->column)}));
    }
    else {
        insSet.emplace_back(INS::genIns(INS::DECLARE, 
                                        node.letMark->line, 
                                        node.letMark->column, 
                                        {sakValue::createStringVal(node.identifier->content, node.identifier->line, node.identifier->column)}));
    }
}
void Generator::generate(AST::AssignStmtNode node) {
    generate(*node.expr);
    generate(*node.iden->idens.at(0), true);
    insSet.emplace_back(INS::genIns(INS::ASSIGN, node.assignOp->line, node.assignOp->column, {}));
}
void Generator::generate(AST::BlockStmtNode node, bool jmpCond) {
    insSet.emplace_back(INS::genIns(INS::NEW_SCOPE, node.leftBrace->line, node.leftBrace->column, {sakValue::createStringVal("[Tag=BlockBegin]", node.leftBrace->line, node.leftBrace->column)}));
    for (auto stmt : node.body) {
        generate(*stmt);
    }

    if (jmpCond) {
        insSet.emplace_back(INS::genIns(INS::PUSH, node.rightBrace->line, node.rightBrace->column, {sakValue::createBoolVal("true", node.rightBrace->line, node.rightBrace->column)}));
    }

    insSet.emplace_back(INS::genIns(INS::END_SCOPE, node.rightBrace->line, node.rightBrace->column, {sakValue::createStringVal("[Tag=BlockEnd]", node.rightBrace->line, node.rightBrace->column)}));
}
// Tag解析：
// [True-in]: 如果条件结果为真则JMP入该scope执行代码
// [Tag=XXXX]: 打上Tag,证明这个scope的作用是什么，e.g. Tag=IfBegin标志着if下的scope开始
// [Finish-out]: 表示如果内部代码被执行则直接跳出if-elseif-else控制流
void Generator::generate(AST::IfStmtNode node) {
    insSet.emplace_back(INS::genIns(INS::NEW_SCOPE, node.left->line, node.left->column, {sakValue::createStringVal("[Tag=IfGroupBegin]", node.ifMark->line, node.ifMark->column)}));

    generate(*node.condition);
    insSet.emplace_back(INS::genIns(INS::JMP, node.ifMark->line, node.ifMark->column, {sakValue::createStringVal("[True-in]", node.ifMark->line, node.ifMark->column)}));
    
    generate(*node.bodyBlock, true);

    insSet.emplace_back(INS::genIns(INS::JMP, node.ifMark->line, node.ifMark->column, {sakValue::createStringVal("[Finish-out]", node.ifMark->line, node.ifMark->column)}));

    if (!node.elseIfstmts.empty()) {
        for (auto elseIfStmt : node.elseIfstmts) {
            generate(*elseIfStmt);
        }
    }

    if (node.elseStmt) {
        generate(*node.elseStmt);
    }
    insSet.emplace_back(INS::genIns(INS::END_SCOPE, node.right->line, node.right->column, {sakValue::createStringVal("[Tag=IfGroupEnd]", node.ifMark->line, node.ifMark->column)}));
}
void Generator::generate(AST::ElseIfStmtNode node) {
    generate(*node.condition);
    insSet.emplace_back(INS::genIns(INS::JMP, node.ifMark->line, node.ifMark->column, {sakValue::createStringVal("[True-in]", node.ifMark->line, node.ifMark->column)}));
    
    generate(*node.bodyBlock, true);
    
    insSet.emplace_back(INS::genIns(INS::JMP, node.ifMark->line, node.ifMark->column, {sakValue::createStringVal("[Finish-out]", node.ifMark->line, node.ifMark->column)}));
}
void Generator::generate(AST::ElseStmtNode node) {
    generate(*node.bodyBlock, true);
}
void Generator::generate(AST::MatchStmtNode node) {
    insSet.emplace_back(INS::genIns(INS::NEW_SCOPE, node.left->line, node.left->column, {sakValue::createStringVal("[Tag=MatchGroupBegin]", node.matchMark->line, node.matchMark->column)}));

    for (auto block : node.matchBlocks) {
        generate(*node.identifier);
        generate(*block->caseExpr);
        insSet.emplace_back(INS::genIns(INS::LGC_EQU, block->caseOp->line, block->caseOp->column, {}));

        insSet.emplace_back(INS::genIns(INS::JMP, block->caseOp->line, block->caseOp->column, {sakValue::createStringVal("[True-in]", block->caseOp->line, block->caseOp->column)}));

        generate(*block->bodyBlock, true);
        
        insSet.emplace_back(INS::genIns(INS::JMP, block->caseOp->line, block->caseOp->column, {sakValue::createStringVal("[Finish-out]", block->caseOp->line, block->caseOp->column)}));
    }
    if (node.defaultBlock) {
        generate(*node.defaultBlock, true);
    }

    insSet.emplace_back(INS::genIns(INS::END_SCOPE, node.rightBrace->line, node.rightBrace->column, {sakValue::createStringVal("[Tag=MatchGroupEnd]", node.matchMark->line, node.matchMark->column)}));
}
void Generator::generate(AST::WhileStmtNode node) {
    insSet.emplace_back(INS::genIns(INS::NEW_SCOPE, node.left->line, node.left->column, {sakValue::createStringVal("[Tag=WhileGroupBegin]", node.whileMark->line, node.whileMark->column)}));

    generate(*node.condition);
    insSet.emplace_back(INS::genIns(INS::JMP, node.whileMark->line, node.whileMark->column, {sakValue::createStringVal("[True-in]", node.whileMark->line, node.whileMark->column)}));

    generate(*node.bodyBlock, true);

    insSet.emplace_back(INS::genIns(INS::JMP, node.whileMark->line, node.whileMark->column, {sakValue::createStringVal("[Loop-back]", node.whileMark->line, node.whileMark->column)}));

    insSet.emplace_back(INS::genIns(INS::END_SCOPE, node.right->line, node.right->column, {sakValue::createStringVal("[Tag=WhileGroupEnd]", node.whileMark->line, node.whileMark->column)}));
}

void Generator::generate(AST::StmtNode node) {
    if (node.assignStmt) generate(*node.assignStmt);
    else if (node.letStmt) generate(*node.letStmt);
    else if (node.ifStmt) generate(*node.ifStmt);
    else if (node.matchStmt) generate(*node.matchStmt);
    else if (node.whileStmt) generate(*node.whileStmt);
    else if (node.blockStmt) generate(*node.blockStmt);
}
