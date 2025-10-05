#ifndef SAKORA_PARSERERROR_H
#define SAKORA_PARSERERROR_H

#include "BasicError.h"

namespace ParserError {
    class WrongMatchError : public SakoraError {
        std::string expected;
    public:
        WrongMatchError(std::string s, std::string ept, int ln, int col);
        void print() override;
    };

    class NotCloseRoundBracketsError : public SakoraError {
    public:
        NotCloseRoundBracketsError(std::string s, int ln, int col);
        void print() override;
    };

    class InvalidControlStmtError : public SakoraError {
    public:
        InvalidControlStmtError(int ln, int col);
        void print() override;
    };
}

#endif