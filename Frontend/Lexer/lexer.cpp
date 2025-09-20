#pragma GCC optimize(3,"Ofast","inline")
#include "lexer.h"

void Lexer::Token::print() {
    std::cout << this->toString() << std::endl;
}

std::string Lexer::Token::toString() {
    std::string typeStr;
    switch (type)
    {
    case Lexer::Identifier:
        typeStr = "Identifier";
        break;
    case Lexer::Symbol:
        typeStr = "Symbol";
        break;
    case Lexer::Number:
        typeStr = "Number";
        break;
    case Lexer::Keyword: 
        typeStr = "Keyword";    
        break;
    case Lexer::String:
        typeStr = "String";
        break;
    case Lexer::Char:
        typeStr = "Char";
        break;
    case Lexer::EndFlag:
        typeStr = "EndFlag";
        break;

    default:
        typeStr = "Unknown";
        break;
    }
    return "<" + typeStr + ", " + content + ">";
}

void Lexer::LexerInstance::next() {
    col ++;
    i ++;
}

Lexer::TokenSequence Lexer::LexerInstance::startLexer(std::string raw) {
    char current;
    Lexer::TokenSequence sequence;

    while (true) {
        current = raw.at(i);

        if (current == '\n') {
            ln += 1;
            col = 1;
            next();
        }
        else if (current == '\0') break;

        if (isalpha(current)) {
            std::string out;
        
            while ((isalpha(raw.at(i)) || isdigit(raw.at(i)))) {
                out.push_back(raw.at(i));
                next();
            }
            
            // 判断是否为关键字
            bool isFinish = false;
            for (auto s: Lexer::KeywordTable) {
                if (s == out) {
                    sequence.emplace_back(Lexer::Keyword, out, ln ,col);
                    isFinish = true;
                }
            }

            if (!isFinish) {
                sequence.emplace_back(Lexer::Identifier, out, ln ,col);
            }
        }
        else if (isdigit(current)) {
            std::string out;

            bool hasDot = false;
            while ((isdigit(raw.at(i))) || raw.at(i) == '.') {
                if (hasDot && raw.at(i) == '.') {
                    break;
                }
                else if (!hasDot && raw.at(i) == '.') {
                    out.push_back(raw.at(i));
                }
                else {
                    out.push_back(raw.at(i));
                }

                next();
            }

            sequence.emplace_back(Lexer::Number, out, ln, col);
        }
        else if (current == '\'') {
            std::string out;
            next();
            if (raw.at(i) == '\\') {
                switch (raw.at(i + 1))
                {
                case 'n':
                    out.push_back('\n');
                    break;
                case 't':
                    out.push_back('\t');
                    break;
                case 'b':
                    out.push_back('\b');
                    break;
                case '0':
                    out.push_back('\0');
                    break;
                case '"':
                    out.push_back('"');
                    break;
                case '\\':
                    out.push_back('\\');
                    break;
                default:
                    break;
                }
                next();
                next();
            }
            else {
                out.push_back(raw.at(i));
                next();
            }
            
            if (raw.at(i) != '\'') {
                throw LexerError::MoreCharacterError("MoreCharacterError", ln, col);
            }
            else next();

            sequence.emplace_back(Lexer::Char, out, ln, col);
        }
        else if (current == '"') {
            std::string out = "\"";
            next();
            bool flag = false;
            while (raw.at(i) != '"') {
                if (raw.at(i) == '\0' || raw.at(i) == '\n')
                    throw LexerError::NotCloseStringError("NotCloseStringError", ln, col);
                else if (raw.at(i) == '\\') {
                    switch (raw.at(i + 1))
                    {
                    case 'n':
                        out.push_back('\n');
                        break;
                    case 't':
                        out.push_back('\t');
                        break;
                    case 'b':
                        out.push_back('\b');
                        break;
                    case '0':
                        out.push_back('\0');
                        break;
                    case '"':
                        out.push_back('"');
                        break;
                    case '\\':
                        out.push_back('\\');
                        break;
                    default:
                        break;
                    }
                    next();
                    next();
                }
                else if (flag && raw.at(i) == '"')
                    break;
                else {
                    out.push_back(raw.at(i));
                    next();
                }
                
                flag = true;
            }
            next(); // 跳过'"'

            out += "\"";
            sequence.emplace_back(Lexer::String, out, ln, col);
        }
        else {
            std::string out;
            if (current == '=') {
                if (raw.at(i + 1) == '=') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "==", ln, col);
                }
                else if (raw.at(i + 1) == '>') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "=>", ln, col);
                }
                else {
                    next();
                    sequence.emplace_back(Lexer::Symbol, "=", ln, col);
                }
            }
            else if (current == '+') {
                if (raw.at(i + 1) == '=') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "+=", ln, col);
                }
                else if (raw.at(i + 1) == '+') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "++", ln, col);
                }
                else {
                    next();
                    sequence.emplace_back(Lexer::Symbol, "+", ln, col);
                }
            }
            else if (current == '-') {
                if (raw.at(i + 1) == '=') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "-=", ln, col);
                }
                else if (raw.at(i + 1) == '-') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "--", ln, col);
                }
                else if (raw.at(i + 1) == '>') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "->", ln, col);
                }
                else {
                    next();
                    sequence.emplace_back(Lexer::Symbol, "-", ln, col);
                }
            }
            else if (current == '*') {
                if (raw.at(i + 1) == '*') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "**", ln, col);
                }
                else {
                    next();
                    sequence.emplace_back(Lexer::Symbol, "*", ln, col);
                }
            }
            else if (current == '/') {
                next();
                sequence.emplace_back(Lexer::Symbol, "/", ln, col);
            }
            else if (current == '>') {
                if (raw.at(i + 1) == '>') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, ">>", ln, col);
                }
                else if (raw.at(i + 1) == '=') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, ">=", ln, col);
                }
                else {
                    next();
                    sequence.emplace_back(Lexer::Symbol, ">", ln, col);
                }
            }
            else if (current == '<') {
                if (raw.at(i + 1) == '<') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "<<", ln, col);
                }
                else if (raw.at(i + 1) == '=') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "<=", ln, col);
                }
                else {
                    next();
                    sequence.emplace_back(Lexer::Symbol, "<", ln, col);
                }
            }
            else if (current == '(') {
                next();
                sequence.emplace_back(Lexer::Symbol, "(", ln, col);
            }
            else if (current == ')') {
                next();
                sequence.emplace_back(Lexer::Symbol, ")", ln, col);
            }
            else if (current == '[') {
                next();
                sequence.emplace_back(Lexer::Symbol, "[", ln, col);
            }
            else if (current == ']') {
                next();
                sequence.emplace_back(Lexer::Symbol, "]", ln, col);
            }
            else if (current == '{') {
                next();
                sequence.emplace_back(Lexer::Symbol, "{", ln, col);
            }
            else if (current == '}') {
                next();
                sequence.emplace_back(Lexer::Symbol, "}", ln, col);
            }
            else if (current == '|') {
                next();
                sequence.emplace_back(Lexer::Symbol, "|", ln, col);
            }
            else if (current == '&') {
                next();
                sequence.emplace_back(Lexer::Symbol, "&", ln, col);
            }
            else if (current == '%') {
                next();
                sequence.emplace_back(Lexer::Symbol, "%", ln, col);
            }
            else if (current == ':') {
                next();
                sequence.emplace_back(Lexer::Symbol, ":", ln, col);
            }
            else if (current == ';') {
                next();
                sequence.emplace_back(Lexer::Symbol, ";", ln, col);
            }
            else if (current == ',') {
                next();
                sequence.emplace_back(Lexer::Symbol, ",", ln, col);
            }
            else if (current == '.') {
                next();
                sequence.emplace_back(Lexer::Symbol, ".", ln, col);
            }
            else if (current == '!') {
                if (raw.at(i + 1) == '=') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "!=", ln, col);
                }
                else {
                    next();
                    sequence.emplace_back(Lexer::Symbol, "!", ln, col);
                }
            }
            else if (current == ' ') {
                next();
            }
        }
    }

    sequence.emplace_back(Lexer::EndFlag, "END TOKEN", ln, col);

    return sequence;
}