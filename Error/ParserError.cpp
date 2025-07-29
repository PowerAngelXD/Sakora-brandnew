#include "ParserError.h"
#include <iostream>

namespace ParserError {
    WrongMatchError::WrongMatchError(std::string s, std::string ept, int ln, int col)
        : SakoraError(std::move(s), ln, col), expected(ept) {}

    void WrongMatchError::print() {
        ERROR_HEAD;
        std::cout << "WrongMatchError: Expected: " + expected + ". But got: '" << src << "'" << std::endl;
    }

    NotCloseRoundBracketsError::NotCloseRoundBracketsError(std::string s, int ln, int col)
        : SakoraError(std::move(s), ln, col) {}

    void NotCloseRoundBracketsError::print() {
        ERROR_HEAD;
        std::cout << "NotCloseRoundBracketsError: Round brackets are not closed properly." << std::endl;
    }
}
