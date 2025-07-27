#include "lexer.h"

void Lexer::Token::print() {
    std::cout << "<";
    switch (type)
    {
    case Lexer::Identifier:
        std::cout << "Identifier";
        break;
    case Lexer::Symbol:
        std::cout << "Symbol";
        break;
    case Lexer::Number:
        std::cout << "Number";
        break;
    case Lexer::Keyword: 
        std::cout << "Keyword";    
        break;
    case Lexer::String:
        std::cout << "String";
        break;
    case Lexer::EndFlag:
        std::cout << "END";

    default:
        break;
    }
    std::cout << ", " << content << ">" << std::endl;
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

    while (i < raw.size() - 1) {
        current = raw.at(i);

        if (current == '\n') {
            ln = 1;
            col = 1;
        }

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
        else if (current == '"') {
            std::string out;
            next();
            bool flag = false;
            while (raw.at(i) != '"') {
                if (raw.at(i) == '\0' || raw.at(i) == '\n')
                    throw LexerError::NotCloseStringError("NotCloseStringErro", ln, col);
                else if (flag && raw.at(i) == '"')
                    break;

                out.push_back(raw.at(i));
                next();
                
                flag = true;
            }
            next(); // 跳过'"'

            sequence.emplace_back(Lexer::String, out, ln, col);
        }
        else {
            std::string out;
            if (current == '=') {
                if (raw.at(i + 1) == '=') {
                    i += 2;
                    sequence.emplace_back(Lexer::Symbol, "==", ln, col);
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