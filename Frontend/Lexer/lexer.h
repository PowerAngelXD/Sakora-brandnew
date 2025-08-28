#ifndef SAKORA_LEXER_H
#define SAKORA_LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

/**
 * 词法分析器相关定义
 * Lexer definitions
 * 包含Token结构、Token序列、词法分析器接口等
 * Includes Token struct, Token sequence, lexer interface, etc.
 */
namespace Lexer {
    /**
     * Token结构体 - 表示一个词法单元
     * Token struct - Represents a lexical token
     */
    struct Token {
        std::string content; // token内容 / Token content
        int type;            // token类型 / Token type
        int line;            // 行号 / Line number
        int column;          // 列号 / Column number

        void print();
        std::string toString();
    };

    /**
     * Token序列类型 - 存储所有token
     * TokenSequence type - Stores all tokens
     */
    using TokenSequence = std::vector<Token>;

    /**
     * 词法分析器实例类
     * Lexer instance class
     * 用于将源代码分割为Token序列
     * Used to split source code into token sequence
     */
    class LexerInstance {
        int ln = 1;
        int col = 1;
        std::size_t i = 0;
    public:
        /**
         * 开始词法分析
         * Start lexical analysis
         * @param src 源代码字符串 / Source code string
         * @return Token序列 / Token sequence
         */
        TokenSequence startLexer(const std::string& src);
        void next();
    };
}

#endif