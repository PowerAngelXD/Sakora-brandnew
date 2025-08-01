#include "VMError.h"
#include <iostream>

#define VM_ERROR_HEAD std::cout << "[VMError] at line " << line << ", column " << column << ":\n"

namespace VMError {
    NotMatchedOperatorError::NotMatchedOperatorError(std::string s, int ln, int col)
        : SakoraError(std::move(s), ln, col) {}

    void NotMatchedOperatorError::print() {
        VM_ERROR_HEAD;
        std::cout << "NotMatchedOperatorError: Operator not matched. Target operator: '" << src << "'" << std::endl;
    }

    NotMatchedTypeError::NotMatchedTypeError(std::string s, int ln, int col)
        : SakoraError(std::move(s), ln, col) {}

    void NotMatchedTypeError::print() {
        VM_ERROR_HEAD;
        std::cout << "NotMatchedTypeError: Type not matched. Target operator: '" << src << "'" << std::endl;
    }
}
