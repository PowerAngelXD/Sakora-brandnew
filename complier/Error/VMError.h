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
        NotTidyArrayError(int ln, int col);
        void print() override;
    };

    class TypeInconsistentError : public SakoraError {
        std::string given;
    public:
        TypeInconsistentError(std::string exp, std::string gi, int ln, int col);
        void print() override;
    };

    class AlreadyIdentifierError : public SakoraError {
        std::string given;
    public:
        AlreadyIdentifierError(std::string s, int ln, int col);
        void print() override;
    };

    class UnknownIdentifierError : public SakoraError {
        std::string given;
    public:
        UnknownIdentifierError(std::string s, int ln, int col);
        void print() override;
    };

    class ArrayOutOfRangeError : public SakoraError {
        std::string given;
    public:
        ArrayOutOfRangeError(int ln, int col);
        void print() override;
    };

    class UseNullValueError : public SakoraError {
        std::string given;
    public:
        UseNullValueError(int ln, int col);
        void print() override;
    };
}

#endif