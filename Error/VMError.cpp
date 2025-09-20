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
    std::cout << "NotMatchedTypeError: Type not matched. Target type: '" << src << "'" << std::endl;
}

VMError::NotTidyArrayError::NotTidyArrayError(int ln, int col)
: SakoraError("NotTidyArrayError", ln, col) {}
void VMError::NotTidyArrayError::print() {
    VM_ERROR_HEAD;
    std::cout << "NotTidyArrayError: The target array is not tidy." << std::endl;
}

VMError::TypeInconsistentError::TypeInconsistentError(std::string exp, std::string gi, int ln, int col)
    : SakoraError(std::move(exp), ln, col), given(gi) {}

void VMError::TypeInconsistentError::print() {
    VM_ERROR_HEAD;
    std::cout << "TypeInconsistentError: The expected type \"" << src << "\" does not coincide with the type \"" << given << "\" of the given value." << std::endl;
}

VMError::AlreadyIdentifierError::AlreadyIdentifierError(std::string s, int ln, int col) 
    : SakoraError(std::move(s), ln, col) {}
void VMError::AlreadyIdentifierError::print() {
    VM_ERROR_HEAD;
    std::cout << "AlreadyIdentifierError: The identifier: \"" << src << "\" has already existed." <<std::endl;
}

VMError::UnknownIdentifierError::UnknownIdentifierError(std::string s, int ln, int col)
    : SakoraError(std::move(s), ln, col) {}
void VMError::UnknownIdentifierError::print() {
    VM_ERROR_HEAD;
    std::cout << "UnknowIdentifierError: The identifier: \"" << src << "\" is not exist in current scope." <<std::endl;
}

VMError::ArrayOutOfRangeError::ArrayOutOfRangeError(int ln, int col) 
    : SakoraError("ArrayOutOfRangeError", ln, col) {}
void VMError::ArrayOutOfRangeError::print() {
    VM_ERROR_HEAD;
    std::cout << "ArrayOutOfRangeError: Occured out of range when accessing array elements." <<std::endl;
}

VMError::UseNullValueError::UseNullValueError(int ln, int col) 
    : SakoraError("UseNullValueError", ln, col) {}
void VMError::UseNullValueError::print() {
    VM_ERROR_HEAD;
    std::cout << "UseNullValueError: Try to use a null value." <<std::endl;
}
