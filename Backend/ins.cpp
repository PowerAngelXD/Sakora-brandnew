#include "ins.h"

namespace INS {
    Instruction::Instruction(InsOp op, int ln, int col, std::initializer_list<std::any> paras)
        : instruction(op), line(ln), column(col), args(paras) {}

    Instruction::Instruction(InsOp op, int ln, int col)
        : instruction(op), line(ln), column(col) {}

    const int& Instruction::getLine() {
        return line;
    }

    const int& Instruction::getColumn() {
        return column;
    }

    const InsOp& Instruction::getOp() {
        return instruction;
    }
}
