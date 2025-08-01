#include "LexerError.h"

#define LEXER_ERROR_HEAD std::cout << "[LexerError] at line " << line << ", column " << column << ":\n";

LexerError::NotExpectError::NotExpectError(std::string s, int ln, int col): SakoraError(std::move(s), ln, col) {}

void LexerError::NotExpectError::print() {
    LEXER_ERROR_HEAD
    std::cout << "NotExpectError: \nThe lexer requires a suitable token, but the provided token is: '" << src << "'" <<std::endl;
}

LexerError::NotCloseStringError::NotCloseStringError(std::string s, int ln, int col): SakoraError(std::move(s), ln, col) {}

void LexerError::NotCloseStringError::print() {
    LEXER_ERROR_HEAD
    std::cout << "NotCloseStringError: \nThe quotation marks of the string are not closed."<<std::endl;
}