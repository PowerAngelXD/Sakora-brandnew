#ifndef SAKORA_CONSOLE_H
#define SAKORA_CONSOLE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include "../Frontend/Lexer/lexer.h"
#include "../Frontend/Parser/parser.h"

namespace sakoraConsole {
    class sakConsole {
    public:
        std::string instanceName;
        
        sakConsole();
        sakConsole(std::string name);

        std::vector<std::string> split(std::string raw, char c);
        void run();
    private:
        std::vector<std::string> contentList;
        int cursor;
    };
}

#endif