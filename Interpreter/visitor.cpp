#include "visitor.h"

sakora::VMCode sakora::CodeMaker::PUSH(std::string value, int ln, int col) {
    return VMCode(sakora::PUSH, ln, col, {value});
}

sakora::VMCode sakora::CodeMaker::ADD() {
    return VMCode(sakora::ADD, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::SUB() {
    return VMCode(sakora::SUB, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::DIV() {
    return VMCode(sakora::DIV, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::MUL() {
    return VMCode(sakora::MUL, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_EQU() {
    return VMCode(sakora::LGC_EQU, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_AND() {
    return VMCode(sakora::LGC_AND, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_OR() {
    return VMCode(sakora::LGC_OR, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_LS_THAN() {
    return VMCode(sakora::LGC_LS_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_MR_THAN() {
    return VMCode(sakora::LGC_MR_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_LSEQU_THAN() {
    return VMCode(sakora::LGC_LSEQU_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_MREQU_THAN() {
    return VMCode(sakora::LGC_MREQU_THAN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_NOT() {
    return VMCode(sakora::LGC_NOT, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::LGC_NOT_EQU() {
    return VMCode(sakora::LGC_NOT_EQU, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::ARR_MAKE(std::string size, int ln, int col) {
    return VMCode(sakora::ARR_MAKE, ln, col, {size});
}

sakora::VMCode sakora::CodeMaker::ARR_TIDY_CHK(int ln, int col) {
    return VMCode(sakora::ARR_TIDY_CHK, ln, col, {});
}

sakora::VMCode sakora::CodeMaker::DECLARE(std::string name, int ln, int col) {
    return VMCode(sakora::DECLARE, ln, col, {name});
}

sakora::VMCode sakora::CodeMaker::ASSIGN(std::string name, int ln, int col) {
    return VMCode(sakora::ASSIGN, ln, col, {name});
}

sakora::VMCode sakora::CodeMaker::GET(std::string name, int ln, int col) {
    return VMCode(sakora::GET, ln, col, {name});
}

sakora::VMCode sakora::CodeMaker::FROM(std::string type, int ln, int col) {
    return VMCode(sakora::FROM, ln, col, {type});
}

sakora::VMCode sakora::CodeMaker::NEW_SCOPE() {
    return VMCode(sakora::NEW_SCOPE, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::END_SCOPE() {
    return VMCode(sakora::END_SCOPE, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::FLAG(std::string flag_name) {
    return VMCode(sakora::FLAG, 0, 0, {flag_name});
}

sakora::VMCode sakora::CodeMaker::JTIN() {
    return VMCode(sakora::JTIN, 0, 0, {});
}

sakora::VMCode sakora::CodeMaker::JTBCK() {
    return VMCode(sakora::JTBCK, 0, 0, {});
}
