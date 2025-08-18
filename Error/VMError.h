#ifndef SAKORA_VMERROR_H
#define SAKORA_VMERROR_H

#include "BasicError.h"

namespace VMError {
    class NotMatchedOperatorError : public SakoraError {
    public:
        NotMatchedOperatorError(std::string s, int ln, int col);
        void print() override;
    };

    class NotMatchedTypeError : public SakoraError {
    public:
        NotMatchedTypeError(std::string s, int ln, int col);
        void print() override;
    };

    class NotTidyArrayError : public SakoraError {
    public:
        NotTidyArrayError(std::string s, int ln, int col);
        void print() override;
    };
}

#endif