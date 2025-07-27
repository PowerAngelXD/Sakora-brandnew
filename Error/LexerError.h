#ifndef LEXERERROR_H
#define LEXERERROR_H
#include "BasicError.h"
#include <exception>

namespace LexerError {
    class NotExpectError : public SakoraError {
    public:
        NotExpectError(std::string s, int ln, int col);
        void print() override;
    };

    class NotCloseStringError : public SakoraError {
    public:
        NotCloseStringError(std::string s, int ln, int col);
        void print() override;
    };
}

#endif