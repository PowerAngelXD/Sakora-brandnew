#ifndef SAKORA_INS_H
#define SAKORA_INS_H

#include <iostream>
#include <vector>
#include <any>
#include <sstream>

#include "env/value.h"

namespace INS {
    enum InsOp {NULL_CMD, PUSH, POP, ADD, 
                SUB, MUL, DIV, LGC_AND, 
                LGC_OR, LGC_NOT_EQU, LGC_EQU, LGC_MR_THAN, 
                LGC_LS_THAN, LGC_MREQU_THAN, LGC_LSEQU_THAN, LGC_NOT,
                ARR_MAKE, ARR_TIDY_CHK, 
                DECLARE, ASSIGN, GET_VAL, GET_OBJ, FROM, PUSH_OBJ,
                };

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
        const sakValue& getPara(std::size_t i = 0);
        std::vector<sakValue> getParas();

        std::string toString();
        void print();
    };

    Instruction genIns(InsOp op, int ln, int col, std::initializer_list<sakValue> paras);
}

#endif