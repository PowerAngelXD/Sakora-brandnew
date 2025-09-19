

#include "instruction.h"

sakora::VMCode sakora::CodeMaker::add() {
    return VMCode(sakora::ADD, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::sub() {
    return VMCode(sakora::SUB, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::mul() {
    return VMCode(sakora::MUL, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::div() {
    return VMCode(sakora::DIV, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcEqu() {
    return VMCode(sakora::LGC_EQU, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcAnd() {
    return VMCode(sakora::LGC_AND, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcOr() {
    return VMCode(sakora::LGC_OR, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcLsThan() {
    return VMCode(sakora::LGC_LS_THAN, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcMrThan() {
    return VMCode(sakora::LGC_MR_THAN, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcLsEquThan() {
    return VMCode(sakora::LGC_LSEQU_THAN, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcMrEquThan() {
    return VMCode(sakora::LGC_MREQU_THAN, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcNot() {
    return VMCode(sakora::LGC_NOT, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::lgcNotEqu() {
    return VMCode(sakora::LGC_NOT_EQU, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::arrMake(std::string size, int ln, int col) {
    return VMCode(sakora::ARR_MAKE, ln, col, {size});
}
sakora::VMCode sakora::CodeMaker::arrTidyChk(int ln, int col) {
    return VMCode(sakora::ARR_TIDY_CHK, ln, col, {});
}
sakora::VMCode sakora::CodeMaker::declare(std::string name, std::string hasMod, int ln, int col) {
    return VMCode(sakora::DECLARE, ln, col, {name, hasMod});
}
sakora::VMCode sakora::CodeMaker::assign(int ln, int col) {
    return VMCode(sakora::ASSIGN, ln, col, {});
}
sakora::VMCode sakora::CodeMaker::get(std::string name, int ln, int col) {
    return VMCode(sakora::GET, ln, col, {name});
}
sakora::VMCode sakora::CodeMaker::from(std::string type, int ln, int col) {
    return VMCode(sakora::FROM, ln, col, {type});
}
sakora::VMCode sakora::CodeMaker::blockStart() {
    return VMCode(sakora::BLOCK_START, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::blockEnd() {
    return VMCode(sakora::BLOCK_END, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::flag(std::string flag_name) {
    return VMCode(sakora::FLAG, 0, 0, {flag_name});
}
sakora::VMCode sakora::CodeMaker::jtin() {
    return VMCode(sakora::JTIN, 0, 0, {});
}
sakora::VMCode sakora::CodeMaker::jtbck() {
    return VMCode(sakora::JTBCK, 0, 0, {});
}
