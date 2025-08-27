#include "parser.h"

Parser::Parser(Lexer::TokenSequence s) {
    seq = s;
}

const Lexer::Token& Parser::peek(int offset)
{
    return seq.at(index + offset);
}

const Lexer::Token& Parser::eat() {
    return seq.at(index ++);
}


// Expression



bool Parser::isPrimExpr() {
    return peek().content == "!" || isArrayExpr() 
            || peek().content == "-" || peek().type == Lexer::Number || peek().type == Lexer::Identifier
            || peek().type == Lexer::String || peek().type == Lexer::Char || peek().content == "(" 
            || peek().content == "true" || peek().content == "false";
}

bool Parser::isCallingExpr() {
    return peek().type == Lexer::Identifier || (peek().type == Lexer::Identifier && peek(1).content == "(");
}
bool Parser::isIdentifierExpr() {
    return isAtomIdentifier();
}
bool Parser::isAtomIdentifier() {
    return isCallingExpr();
}

bool Parser::isAddExpr() {
    return isPrimExpr();
}

bool Parser::isMulExpr() {
    return isAddExpr();
}

bool Parser::isLogicExpr() {
    if (peek().content == "true" || peek().content == "false" || peek().content == "!") return true;
    if (isArrayExpr()) {
        auto pos = index;
        parseArrayExpr();
        if (peek().content == "==" || peek().content == "!=" || peek().content == ">=" || peek().content == "<=" || peek().content == ">" || peek().content == "<") {
            index = pos;
            return true;
        }
        else {
            index = pos;
            return false;
        }
    }
    else if (isAddExpr()) {
        auto pos = index;
        parseAddExpr();
        if (peek().content == "==" || peek().content == "!=" || peek().content == ">=" || peek().content == "<=" || peek().content == ">" || peek().content == "<") {
            index = pos;
            return true;
        }
        else {
            index = pos;
            return false;
        }
    }
    else if (isTypeExpr()) {
        auto pos = index;
        parseTypeExpr();
        if (peek().content == "==" || peek().content == "!=" || peek().content == ">=" || peek().content == "<=" || peek().content == ">" || peek().content == "<") {
            index = pos;
            return true;
        }
        else {
            index = pos;
            return false;
        }
    }
    else return false;
}

bool Parser::isBoolExpr() {
    return isLogicExpr();
}

bool Parser::isPrimTypeExpr() {
    return peek().type == Lexer::Keyword || peek().type == Lexer::Identifier;
}

bool Parser::isArrayTypeExpr() {
    if (isPrimTypeExpr()) {
        if (peek(1).content == "[") return true;
        else return false;
    }
    else return false;
}

bool Parser::isTypeExpr() {
    return isPrimTypeExpr() || isArrayTypeExpr();
}

bool Parser::isArrayExpr() {
    return peek().content == "[";
}


bool Parser::isWholeExpr() {
    return (isAddExpr() || isBoolExpr()) && !isAssignStmt();
}

std::shared_ptr<AST::PrimExprNode> Parser::parsePrimExpr() {
    if (!isPrimExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Literal Or Expression", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::PrimExprNode>();
    if (peek().content == "!" || peek().content == "-") {
        node->prefixOp = std::make_shared<Lexer::Token>(eat());
    }

    if (peek().content == "(") {
        eat();
        node->wholeExpr = parseWholeExpr();
        eat();
        return node;
    }
    else if (peek().content == "[") {
        node->arrayExpr = parseArrayExpr();
        return node;
    }
    else if (isIdentifierExpr()) {
        node->iden = parseIdentifierExpr();
        return node;
    }
    else {
        node->literal = std::make_shared<Lexer::Token>(eat());
        return node;
    }
}

std::shared_ptr<AST::CallingExprNode> Parser::parseCallingExpr() {
    if(!isCallingExpr())
        throw ParserError::WrongMatchError(peek().content, "identifier", peek().line, peek().column);
    
    auto node = std::make_shared<AST::CallingExprNode>();

    node->iden = std::make_shared<Lexer::Token>(eat());

    if (peek().content == "(") {
        node->left = std::make_shared<Lexer::Token>(eat());

        if (isWholeExpr()) {
            // 函数存在参数，开始解析参数列表
            node->args.emplace_back(parseWholeExpr());
            while (peek().content == ",") {
                node->dots.emplace_back(std::make_shared<Lexer::Token>(eat()));
                if (!isWholeExpr())
                    throw ParserError::WrongMatchError(peek().content, "An expression", peek().line, peek().column);
                    
                node->args.emplace_back(parseWholeExpr());
            }
        }

        if (peek().content != ")")
            throw ParserError::WrongMatchError(peek().content, "')'", peek().line, peek().column);  
        
        node->right = std::make_shared<Lexer::Token>(eat());
    }

    return node;
}

std::shared_ptr<AST::AtomIdentifierNode> Parser::parseAtomIdentifier() {
    if (!isAtomIdentifier())
        throw ParserError::WrongMatchError(peek().content, "Identifier", peek().line, peek().column);  
    
    auto node = std::make_shared<AST::AtomIdentifierNode>();

    node->iden = parseCallingExpr();

    while (peek().content == "[") {
        auto indexOp = std::make_shared<AST::AtomIdentifierNode::getIndexOp>();
        indexOp->left = std::make_shared<Lexer::Token>(eat());

        if (!isAddExpr()) 
            throw ParserError::WrongMatchError(peek().content, "An add expression as index", peek().line, peek().column);  

        indexOp->index = parseAddExpr();
        
        if (peek().content != "]")
            throw ParserError::WrongMatchError(peek().content, "']'", peek().line, peek().column);  

        indexOp->right = std::make_shared<Lexer::Token>(eat());

        node->getIndexOps.emplace_back(indexOp);
    }

    return node;
}

std::shared_ptr<AST::IdentifierExprNode> Parser::parseIdentifierExpr() {
    if (!isIdentifierExpr())
        throw ParserError::WrongMatchError(peek().content, "Identifier", peek().line, peek().column);  
    
    auto node = std::make_shared<AST::IdentifierExprNode>();

    node->idens.emplace_back(parseAtomIdentifier());

    while (peek().content == ".") {
        node->getOps.emplace_back(std::make_shared<Lexer::Token>(eat()));

        if (!isIdentifierExpr())
            throw ParserError::WrongMatchError(peek().content, "Identifier", peek().line, peek().column);  
        
        node->idens.emplace_back(parseAtomIdentifier());
    }

    return node;
}

std::shared_ptr<AST::MulExprNode> Parser::parseMulExpr() {
    if (!isMulExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Literal Or Expression", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::MulExprNode>();
    node->prims.emplace_back(parsePrimExpr());
    while ((peek().content == "*" || peek().content == "/") && peek().type == Lexer::Symbol) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->prims.emplace_back(parsePrimExpr());
    }

    return node;
}

std::shared_ptr<AST::AddExprNode> Parser::parseAddExpr() {
    if (!isMulExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Literal Or Expression", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::AddExprNode>();
    node->muls.emplace_back(parseMulExpr());
    while ((peek().content == "+" || peek().content == "-") && peek().type == Lexer::Symbol) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->muls.emplace_back(parseMulExpr());
    }

    return node;
}

std::shared_ptr<AST::LogicExprNode> Parser::parseLogicExpr() {
    if (!isLogicExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Logic Operator", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::LogicExprNode>();
    node->adds.emplace_back(parseAddExpr());
    while ((peek().content == "==" || peek().content == "!=" || peek().content == ">=" || peek().content == "<=" || peek().content == ">" || peek().content == "<") && peek().type == Lexer::Symbol) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->adds.emplace_back(parseAddExpr());
    }

    return node;
}

std::shared_ptr<AST::BoolExprNode> Parser::parseBoolExpr() {
    if (!isBoolExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Boolean Operator", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::BoolExprNode>();
    node->lgcs.emplace_back(parseLogicExpr());
    while ((peek().content == "and" || peek().content == "or") && peek().type == Lexer::Keyword) {
        node->ops.emplace_back(std::make_shared<Lexer::Token>(eat()));
        node->lgcs.emplace_back(parseLogicExpr());
    }

    return node;
}

std::shared_ptr<AST::PrimTypeExprNode> Parser::parsePrimTypeExpr() {
    if (!isPrimTypeExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Type Identifier", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::PrimTypeExprNode>();
    node->identifier = std::make_shared<Lexer::Token>(eat());

    return node;
}

std::shared_ptr<AST::ArrayTypeExprNode> Parser::parseArrayTypeExpr() {
    if (!isArrayTypeExpr()) {
        throw ParserError::WrongMatchError(peek().content, "Type Identifier And ArraySymbol", peek().line, peek().column);
    }
    auto node = std::make_shared<AST::ArrayTypeExprNode>();

    node->primType = parsePrimTypeExpr();
    
    while (peek().content == "[") {
        auto info = std::make_shared<AST::ArrayTypeExprNode::ArrayInfoOpNode>();
        info->leftArrayModOp = std::make_shared<Lexer::Token>(eat());
        if (peek().type != Lexer::Number) {
            throw ParserError::WrongMatchError(peek().content, "Number", peek().line, peek().column);
        }
        info->length = std::make_shared<Lexer::Token>(eat());
        if (peek().content != "]") {
            throw ParserError::WrongMatchError(peek().content, "']'", peek().line, peek().column);
        }
        info->rightArrayModOp = std::make_shared<Lexer::Token>(eat());

        node->arrayInfos.emplace_back(info);
    }

    return node;
}

std::shared_ptr<AST::TypeExprNode> Parser::parseTypeExpr() {
    auto node = std::make_shared<AST::TypeExprNode>();
    
    if (isArrayTypeExpr()) node->array = parseArrayTypeExpr();
    else node->prim = parsePrimTypeExpr();

    return node;
}

std::shared_ptr<AST::ArrayExprNode> Parser::parseArrayExpr() {
    if (!isArrayExpr()) {
        throw ParserError::WrongMatchError(peek().content, "'['", peek().line, peek().column);
    }

    auto node = std::make_shared<AST::ArrayExprNode>();

    node->leftArrayModOp = std::make_shared<Lexer::Token>(eat());

    // [1,2,3,4]
    while (isAddExpr()) {
        node->elements.emplace_back(parseAddExpr());
        if (peek().content != ",") {
            if (peek().content == "]") break;
            else 
                throw ParserError::WrongMatchError(peek().content, "','", peek().line, peek().column);
        }
        node->dots.emplace_back(std::make_shared<Lexer::Token>(eat()));
    }

    if (peek().content != "]") {
        throw ParserError::WrongMatchError(peek().content, "']'", peek().line, peek().column);
    }
    node->rightArrayModOp = std::make_shared<Lexer::Token>(eat());

    return node;
}


std::shared_ptr<AST::WholeExprNode> Parser::parseWholeExpr() {
    auto node = std::make_shared<AST::WholeExprNode>();

    if (isBoolExpr()) node->boolExpr = parseBoolExpr();
    //else if (isTypeExpr()) node->typeExpr = parseTypeExpr();
    else node->addExpr = parseAddExpr();

    return node;
}


// Statement


bool Parser::isLetStmt() {
    return peek().content == "let";
}

bool Parser::isAssignStmt() {
    if (isIdentifierExpr()) {
        auto pos = index;
        parseIdentifierExpr();
        if (peek().content == "=") {
            index = pos;
            return true;
        }
        else {
            index = pos;
            return false;
        }
    }
    return false;
}

bool Parser::isBlockStmt() {
    return peek().content == "{";
}

bool Parser::isIfStmt() {
    return peek().content == "if";
}

bool Parser::isElseIfStmt() {
    return peek().content == "else" && peek(1).content == "if";
}

bool Parser::isElseStmt() {
    return peek().content == "else" && peek(1).content == "{";
}

bool Parser::isMatchStmt() {
    return peek().content == "match";
}


std::shared_ptr<AST::LetStmtNode> Parser::parseLetStmt() {
    if (!isLetStmt())
        throw ParserError::WrongMatchError(peek().content, "\"let\"", peek().line, peek().column);

    auto node = std::make_shared<AST::LetStmtNode>();
    node->letMark = std::make_shared<Lexer::Token>(eat());

    if (!peek().type == Lexer::Identifier) 
        throw ParserError::WrongMatchError(peek().content, "Identifier", peek().line, peek().column);
    node->identifier = std::make_shared<Lexer::Token>(eat());

    // 存在类型标注符
    if (peek().content == ":") {
        node->typeModOp = std::make_shared<Lexer::Token>(eat());
        if (!isTypeExpr())
            throw ParserError::WrongMatchError(peek().content, "TypeExpression", peek().line, peek().column);
        
        node->type = parseTypeExpr();
    }

    if (peek().content == "=") {
         node->assignOp = std::make_shared<Lexer::Token>(eat());

        if (!isWholeExpr()) 
            throw ParserError::WrongMatchError(peek().content, "Value or Expression", peek().line, peek().column);
        node->expr = parseWholeExpr();
    }
    else if (peek().content != "=" && !node->typeModOp)
        throw ParserError::WrongMatchError(peek().content, "'='", peek().line, peek().column); // 如果没有指定类型不能进行声明，如：let a;

    if (peek().content != ";") 
        throw ParserError::WrongMatchError(peek().content, "';'", peek().line, peek().column);
    node->stmtEndOp = std::make_shared<Lexer::Token>(eat());

    return node;
}

std::shared_ptr<AST::AssignStmtNode> Parser::parseAssignStmt() {
    if (!isAssignStmt())
        throw ParserError::WrongMatchError(peek().content, "Assign Statement", peek().line, peek().column);
    
    auto node = std::make_shared<AST::AssignStmtNode>();
    node->iden = parseIdentifierExpr();
    node->assignOp = std::make_shared<Lexer::Token>(eat());

    if (!isWholeExpr()) 
        throw ParserError::WrongMatchError(peek().content, "Value or Expression", peek().line, peek().column);
    node->expr = parseWholeExpr();

    if (peek().content != ";") 
        throw ParserError::WrongMatchError(peek().content, "';'", peek().line, peek().column);
    node->stmtEndOp = std::make_shared<Lexer::Token>(eat());

    return node;
}

std::shared_ptr<AST::BlockStmtNode> Parser::parseBlockStmt() {
    if (!isBlockStmt())
        throw ParserError::WrongMatchError(peek().content, "'{'", peek().line, peek().column);
    
    auto node = std::make_shared<AST::BlockStmtNode>();
    node->leftBrace = std::make_shared<Lexer::Token>(eat());

    while (isStmt()) {
        node->body.emplace_back(parseStmt());
    }

    if (peek().content != "}")
        throw ParserError::WrongMatchError(peek().content, "'}'", peek().line, peek().column);
    node->rightBrace = std::make_shared<Lexer::Token>(eat());

    return node;
}

std::shared_ptr<AST::IfStmtNode> Parser::parseIfStmt() {
    if (!isIfStmt())
        throw ParserError::WrongMatchError(peek().content, "\"if\"", peek().line, peek().column);

    auto node = std::make_shared<AST::IfStmtNode>();
    node->ifMark = std::make_shared<Lexer::Token>(eat());

    if (peek().content != "(")
        throw ParserError::WrongMatchError(peek().content, "'('", peek().line, peek().column);
    node->left = std::make_shared<Lexer::Token>(eat());
    if (!isBoolExpr())
        throw ParserError::WrongMatchError(peek().content, "Bool Expression", peek().line, peek().column);
    node->condition = parseBoolExpr();
    if (peek().content != ")")
        throw ParserError::WrongMatchError(peek().content, "')'", peek().line, peek().column);
    node->right = std::make_shared<Lexer::Token>(eat());

    node->bodyBlock = parseBlockStmt();

    while (isElseIfStmt()) {
        node->elseIfstmts.emplace_back(parseElseIfStmt());
    }

    if (isElseStmt()) {
        node->elseStmt = parseElseStmt();
    }

    return node;
}

std::shared_ptr<AST::ElseIfStmtNode> Parser::parseElseIfStmt() {
    if (!isElseIfStmt())
        throw ParserError::WrongMatchError(peek().content, "\"else if\"", peek().line, peek().column);

    auto node = std::make_shared<AST::ElseIfStmtNode>();
    node->elseMark = std::make_shared<Lexer::Token>(eat()); // "else"
    node->ifMark = std::make_shared<Lexer::Token>(eat()); // "if"

    if (peek().content != "(")
        throw ParserError::WrongMatchError(peek().content, "'('", peek().line, peek().column);
    node->left = std::make_shared<Lexer::Token>(eat());
    if (!isBoolExpr())
        throw ParserError::WrongMatchError(peek().content, "Bool Expression", peek().line, peek().column);
    node->condition = parseBoolExpr();
    if (peek().content != ")")
        throw ParserError::WrongMatchError(peek().content, "')'", peek().line, peek().column);
    node->left = std::make_shared<Lexer::Token>(eat());

    node->bodyBlock = parseBlockStmt();
    return node;
}

std::shared_ptr<AST::ElseStmtNode> Parser::parseElseStmt() {
    if (!isElseStmt())
        throw ParserError::WrongMatchError(peek().content, "\"else\"", peek().line, peek().column);

    auto node = std::make_shared<AST::ElseStmtNode>();
    node->elseMark = std::make_shared<Lexer::Token>(eat());

    node->bodyBlock = parseBlockStmt();

    return node;
}

std::shared_ptr<AST::MatchStmtNode> Parser::parseMatchStmt() {
    if (!isMatchStmt())
        throw ParserError::WrongMatchError(peek().content, "\"match\"", peek().line, peek().column);

    auto node = std::make_shared<AST::MatchStmtNode>();
    node->matchMark = std::make_shared<Lexer::Token>(eat());

    if (peek().content != "(")
        throw ParserError::WrongMatchError(peek().content, "'('", peek().line, peek().column);
    node->left = std::make_shared<Lexer::Token>(eat());

    if (!isWholeExpr())
        throw ParserError::WrongMatchError(peek().content, "An expression", peek().line, peek().column);
    node->identifier = parseIdentifierExpr();

    if (peek().content != ")")
        throw ParserError::WrongMatchError(peek().content, "')'", peek().line, peek().column);
    node->right = std::make_shared<Lexer::Token>(eat());

    if (peek().content != "{")
        throw ParserError::WrongMatchError(peek().content, "'{'", peek().line, peek().column);
    node->leftBrace = std::make_shared<Lexer::Token>(eat());

    while (isWholeExpr() && peek().content != "default") {
        auto block = std::make_shared<AST::MatchStmtNode::matchBlock>();

        if (!isWholeExpr())
            throw ParserError::WrongMatchError(peek().content, "An expression", peek().line, peek().column);
        block->caseExpr = parseWholeExpr();

        if (peek().content != "=>")
            throw ParserError::WrongMatchError(peek().content, "'=>'", peek().line, peek().column);
        block->caseOp = std::make_shared<Lexer::Token>(eat());

        block->bodyBlock = parseBlockStmt();

        node->matchBlocks.emplace_back(block);
    }
    if (peek().content == "default") {
        node->defaultMark = std::make_shared<Lexer::Token>(eat());
        if (peek().content != "=>")
            throw ParserError::WrongMatchError(peek().content, "'=>'", peek().line, peek().column);
        node->defaultOp = std::make_shared<Lexer::Token>(eat());
        node->defaultBlock = parseBlockStmt();
    }

    if (peek().content != "}")
        throw ParserError::WrongMatchError(peek().content, "'}'", peek().line, peek().column);
    node->rightBrace = std::make_shared<Lexer::Token>(eat());

    return node;
}


bool Parser::isStmt() {
    return isLetStmt() || isAssignStmt() ||isIfStmt() || isElseIfStmt() || isElseStmt() || isBlockStmt() || isMatchStmt();
}

std::shared_ptr<AST::StmtNode> Parser::parseStmt() {
    auto stmt = std::make_shared<AST::StmtNode>();

    if (isLetStmt()) stmt->letStmt = parseLetStmt();
    else if (isAssignStmt()) stmt->assignStmt = parseAssignStmt();
    else if (isIfStmt()) stmt->ifStmt = parseIfStmt();
    else if (isElseIfStmt() || isElseStmt()) throw ParserError::InvalidControlStmtError(peek().line, peek().column);
    else if (isElseStmt()) stmt->elseStmt = parseElseStmt();
    else if (isBlockStmt()) stmt->blockStmt = parseBlockStmt();
    else if (isMatchStmt()) stmt->matchStmt = parseMatchStmt();
    else throw ParserError::WrongMatchError(peek().content, "Statement", peek().line, peek().column);
    return stmt;
}

std::vector<std::shared_ptr<AST::StmtNode>> Parser::parse() {
    std::vector<std::shared_ptr<AST::StmtNode>> stmts;
    while (isStmt()) {
        stmts.emplace_back(parseStmt());
    }
    return stmts;
}

