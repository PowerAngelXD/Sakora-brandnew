#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include "../../Error/LexerError.h"

namespace Lexer {
    enum TokenType { Identifier, Symbol, Number, Keyword, String, EndFlag };
    static std::vector<std::string> KeywordTable = {"let", "if", "else", "and", "or", "int", "float", "char", "true", "false"};

    struct Token {
        TokenType type;
        std::string content;
        int line;
        int column;

        void print();
        std::string toString();
    };

    using TokenSequence = std::vector<Token>;

    class LexerInstance {
        int ln = 1;
        int col = 1;
        std::size_t i = 0;
    public:
        TokenSequence startLexer(std::string raw);
        void next();
    };
}

#endif