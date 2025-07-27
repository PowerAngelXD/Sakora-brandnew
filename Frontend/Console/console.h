#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>
#include "../Lexer/lexer.h"
#include "../Parser/parser.h"

namespace sakoraConsole {
    static std::string version = "ALPHA 0.1";

    class sakConsole {
    public:
        std::string instanceName;
        
        sakConsole();
        sakConsole(std::string name);

        void run();
    private:
        std::vector<std::string> contentList;
        int cursor;
    };
}

#endif