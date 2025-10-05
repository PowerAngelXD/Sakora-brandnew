#ifndef SAKORA_IRCODE_H
#define SAKORA_IRCODE_H

#include "includes/magic_enum.hpp"
#include "sakValue.h"

#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

namespace sakIR {
    enum class IROpcode {
        Nocode, 
        Add, Sub, Mul, Div, Mod,
        Jmp, JmpTrue, JmpFalse, 
        Push, Pop, 
        LgcEqu, LgcMrThan, LgcLsThan, LgcMrequThan, LgcLsequThan,
        MakeArray, MakeTuple
    };

    class IROp {
        IROpcode code;
        int defLine, defColumn;
        std::vector<Value> arguments;
    public:
        IROp(IROpcode irc, int ln, int col);

        std::pair<int, int> getPosition();
        std::vector<Value> getArgs();
        IROpcode getCode();
        
        std::string getCodeString();
        std::string to_string();
    };
}

#endif