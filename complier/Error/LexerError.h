#ifndef SAKORA_LEXERERROR_H
#define SAKORA_LEXERERROR_H
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

    class MoreCharacterError : public SakoraError {
    public:
        MoreCharacterError(std::string s, int ln, int col);
        void print() override;
    };
}

#endif