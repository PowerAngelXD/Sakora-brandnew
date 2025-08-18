#include "VMError.h"
#include <iostream>

#define VM_ERROR_HEAD std::cout << "[VMError] at line " << line << ", column " << column << ":\n"

VMError::NotMatchedOperatorError::NotMatchedOperatorError(std::string s, int ln, int col)
    : SakoraError(std::move(s), ln, col) {}

void VMError::NotMatchedOperatorError::print() {
    VM_ERROR_HEAD;
    std::cout << "NotMatchedOperatorError: Operator not matched. Target operator: '" << src << "'" << std::endl;
}

VMError::NotMatchedTypeError::NotMatchedTypeError(std::string s, int ln, int col)
    : SakoraError(std::move(s), ln, col) {}

void VMError::NotMatchedTypeError::print() {
    VM_ERROR_HEAD;
    std::cout << "NotMatchedTypeError: Type not matched. Target operator: '" << src << "'" << std::endl;
}

VMError::NotTidyArrayError::NotTidyArrayError(std::string s, int ln, int col)
: SakoraError(std::move(s), ln, col) {}

void VMError::NotTidyArrayError::print() {
    VM_ERROR_HEAD;
    std::cout << "NotTidyArrayError: The target array is not tidy." << std::endl;
}
