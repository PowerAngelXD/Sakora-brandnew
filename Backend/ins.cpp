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

const sakValue& INS::Instruction::getPara(std::size_t i) {
    return args.at(i);
}

std::vector<sakValue> INS::Instruction::getParas() {
    return args;
}

INS::Instruction INS::genIns(InsOp op, int ln, int col, std::initializer_list<sakValue> paras) {
    return Instruction(op, ln, col, paras);
}

std::string INS::Instruction::toString() {
    std::ostringstream oss;
    switch (this->instruction) {
        case INS::NULL_CMD:
            oss << "NULL_CMD";
            break;
        case INS::PUSH:
            oss << "PUSH ";
            oss << this->args.at(0).toString();
            break;
        case INS::POP:
            oss << "POP";
            break;  
        case INS::ADD:
            oss << "ADD";
            break;  
        case INS::SUB:  
            oss << "SUB";
            break;
        case INS::MUL:
            oss << "MUL";
            break;
        case INS::DIV:  
            oss << "DIV";
            break;  
        case INS::LGC_AND:
            oss << "LGC_AND";
            break;
        case INS::LGC_OR:
            oss << "LGC_OR";
            break;
        case INS::LGC_NOT_EQU:
            oss << "LGC_NOT_EQU";
            break;
        case INS::LGC_EQU:
            oss << "LGC_EQU";
            break;
        case INS::LGC_MR_THAN:
            oss << "LGC_MR_THAN";
            break;  
        case INS::LGC_LS_THAN:
            oss << "LGC_LS_THAN";
            break;
        case INS::LGC_MREQU_THAN:
            oss << "LGC_MREQU_THAN";
            break;
        case INS::LGC_LSEQU_THAN:
            oss << "LGC_LSEQU_THAN";
            break;
        case INS::LGC_NOT:
            oss << "LGC_NOT";
            break;
        case INS::ARR_MAKE:
            oss << "ARR_MAKE";
            break;
        case INS::ARR_TIDY_CHK:
            oss << "ARR_TIDY_CHK";
            break;
        case INS::DECLARE:
            oss << "DECLARE " << this->args.at(0).toString();
            if (this->args.size() > 1) {
                oss << this->args.at(1).toString();
            }
            break;
        case INS::ASSIGN:
            oss << "ASSIGN " << this->args.at(0).toString();
            break;
        case INS::GET:
            oss << "GET " << this->args.at(0).toString();
            break;    
        case INS::FROM:
            oss << "FROM " << this->args.at(0).toString();
        default:
            break;
    }
    return oss.str();
}
void INS::Instruction::print() {
    std::cout <<this->toString() << std::endl;
}
