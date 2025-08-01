#include "ParserError.h"
#include <iostream>

#define PARSER_ERROR_HEAD std::cout << "[ParserError] at line " << line << ", column " << column << ":\n";

namespace ParserError {
    WrongMatchError::WrongMatchError(std::string s, std::string ept, int ln, int col)
        : SakoraError(std::move(s), ln, col), expected(ept) {}

    void WrongMatchError::print() {
        PARSER_ERROR_HEAD
        std::cout << "WrongMatchError: Expected: " + expected + ". But got: '" << src << "'" << std::endl;
    }

    NotCloseRoundBracketsError::NotCloseRoundBracketsError(std::string s, int ln, int col)
        : SakoraError(std::move(s), ln, col) {}

    void NotCloseRoundBracketsError::print() {
        PARSER_ERROR_HEAD
        std::cout << "NotCloseRoundBracketsError: Round brackets are not closed properly." << std::endl;
    }
}
