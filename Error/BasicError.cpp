#include "BasicError.h"

SakoraError::SakoraError(std::string s, int ln, int col): line(ln), column(col), src(s) {}

std::string SakoraError::what() { return src; }

void SakoraError::print() {
    ERROR_HEAD
    std::cout << "Error: " << src << std::endl;
    std::cout << "Line: " << line << ", Column: " << column << std::endl;
}