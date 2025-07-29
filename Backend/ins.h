#ifndef SAKORA_INS_H
#define SAKORA_INS_H

#include <iostream>
#include <vector>
#include <any>

namespace INS {
    enum InsOp {NULL_CMD, PUSH, POP, ADD, SUB, MUL, DIV};

    class Instruction {
        InsOp instruction;
        int line, column;
        std::vector<std::any> args;
    public:
        Instruction(InsOp op, int ln, int col, std::initializer_list<std::any> paras);
        Instruction(InsOp op, int ln, int col);

        const int& getLine();
        const int& getColumn();
        const InsOp& getOp();
    };
}

#endif