#include "ins.h"


INS::Instruction::Instruction(InsOp op, int ln, int col, std::initializer_list<sakValue> paras)
    : instruction(op), line(ln), column(col), args(paras) {}

INS::Instruction::Instruction(InsOp op, int ln, int col)
    : instruction(op), line(ln), column(col) {}

const int& INS::Instruction::getLine() {
    return line;
}

const int& INS::Instruction::getColumn() {
    return column;
}

const INS::InsOp& INS::Instruction::getOp() {
    return instruction;
}

INS::Instruction INS::genIns(InsOp op, int ln, int col, std::initializer_list<sakValue> paras) {
    return Instruction(op, ln, col, paras);
}
