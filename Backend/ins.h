#ifndef SAKORA_INS_H
#define SAKORA_INS_H

#include <iostream>
#include <vector>
#include <any>

#include "env/value.h"

namespace INS {
    enum InsOp {NULL_CMD, PUSH, POP, ADD, SUB, MUL, DIV, LGC_AND, LGC_OR, LGC_NOT_EQU, LGC_EQU, LGC_MR_THAN, LGC_LS_THAN, LGC_MREQU_THAN, LGC_LSEQU_THAN, LGC_NOT};

    class Instruction {
        InsOp instruction;
        int line, column;
        std::vector<sakValue> args;
    public:
        Instruction(InsOp op, int ln, int col, std::initializer_list<sakValue> paras);
        Instruction(InsOp op, int ln, int col);

        const int& getLine();
        const int& getColumn();
        const InsOp& getOp();
        const sakValue& getParas(std::size_t i = 0);
    };

    Instruction genIns(InsOp op, int ln, int col, std::initializer_list<sakValue> paras);
}

#endif