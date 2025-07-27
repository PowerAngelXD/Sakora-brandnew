#ifndef INS_H
#define INS_H

#include <iostream>
#include <vector>
#include <any>

namespace INS {
    enum InsOp {PUSH, POP, ADD, SUB, MUL, DIV};

    class Instruction {
        int line, column;
        InsOp instruction;
        std::vector<std::any> args;
    public:
        Instruction(InsOp op, int ln, int col, std::initializer_list<std::any> paras);
        Instruction(InsOp op, int ln, int col);

        const int& getLine();
        const int& getColumn();
        const InsOp getOp();
    };
}

#endif