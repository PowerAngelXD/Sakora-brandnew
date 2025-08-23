#include "ParserError.h"
#include <iostream>

#define PARSER_ERROR_HEAD std::cout << "[ParserError] at line " << line << ", column " << column << ":\n";

ParserError::WrongMatchError::WrongMatchError(std::string s, std::string ept, int ln, int col)
    : SakoraError(std::move(s), ln, col), expected(ept) {}

void ParserError::WrongMatchError::print() {
    PARSER_ERROR_HEAD
    std::cout << "WrongMatchError: Expected: " + expected + ". But got: '" << src << "'" << std::endl;
}

ParserError::NotCloseRoundBracketsError::NotCloseRoundBracketsError(std::string s, int ln, int col)
    : SakoraError(std::move(s), ln, col) {}

void ParserError::NotCloseRoundBracketsError::print() {
    PARSER_ERROR_HEAD
    std::cout << "NotCloseRoundBracketsError: Round brackets are not closed properly." << std::endl;
}

ParserError::InvalidControlStmtError::InvalidControlStmtError(int ln, int col) 
    : SakoraError("InvalidControlStmtError", ln, col) {}
void ParserError::InvalidControlStmtError::print() {
    PARSER_ERROR_HEAD
    std::cout << "InvalidControlStmtError: The control flow statements ElseIf and Else must come after the If statement." << std::endl;
}
