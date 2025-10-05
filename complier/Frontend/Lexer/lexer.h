#ifndef SAKORA_LEXER_H
#define SAKORA_LEXER_H

#include <iostream>
#include <vector>
#include "../../Error/LexerError.h"
#include "includes/magic_enum.hpp"

/**
 * Sakora 词法分析器头文件
 * Sakora Lexer Header File
 * 包含Token类型定义、Token结构体、词法分析器类等
 * Includes Token type definitions, Token struct, Lexer class, etc.
 */
namespace Lexer {
    /**
     * TokenType 枚举 - 词法单元类型
     * TokenType Enum - Types of lexical tokens
     * 包括标识符、符号、数字、关键字、字符串、字符、结束标志
     * Includes Identifier, Symbol, Number, Keyword, String, Char, EndFlag
     */
    enum TokenType { Identifier, Symbol, Number, Keyword, String, Char, EndFlag };

    /**
     * 关键字表 - 存储所有语言关键字
     * KeywordTable - Stores all language keywords
     */
    static std::vector<std::string> KeywordTable = {"let", "if", "else", "and", "or", "int", "float", "char", "true", "false",
                                                    "typeof", "mutable", "match", "while", "for", "default"};

    /**
     * Token结构体 - 表示一个词法单元
     * Token struct - Represents a lexical token
     */
    struct Token {
        TokenType type;        // token类型 / Token type
        std::string content;   // token内容 / Token content
        int line;              // 行号 / Line number
        int column;            // 列号 / Column number

        /**
         * 打印token信息
         * Print token information
         */
        void print();
        /**
         * 转换为字符串
         * Convert token to string
         */
        std::string toString();
    };

    /**
     * TokenSequence类型 - 存储所有token
     * TokenSequence type - Stores all tokens
     */
    using TokenSequence = std::vector<Token>;

    /**
     * 词法分析器实例类
     * LexerInstance class
     * 用于将源代码分割为Token序列
     * Used to split source code into token sequence
     */
    class LexerInstance {
        int ln = 1;        // 当前行号 / Current line number
        int col = 1;       // 当前列号 / Current column number
        std::size_t i = 0; // 当前处理字符索引 / Current character index
    public:
        /**
         * 开始词法分析
         * Start lexical analysis
         * @param raw 源代码字符串 / Source code string
         * @return Token序列 / Token sequence
         */
        TokenSequence startLexer(std::string raw);
        /**
         * 处理下一个字符
         * Process next character
         */
        void next();
    };
}

#endif