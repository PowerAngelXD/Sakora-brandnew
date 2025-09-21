
#pragma GCC optimize(3,"Ofast","inline")
#include "instruction.h"


// 构造函数实现
// Constructor implementation
sakora::VMCode::VMCode(sakora::InsOp op, int ln, int col, std::initializer_list<std::string> _args)
    : VMOp(op), args(_args), line(ln), column(col) {}

// 获取指令操作码
// Get instruction opcode
const sakora::InsOp& sakora::VMCode::getOp() {
    return VMOp;
}

// 获取所有参数
// Get all arguments
std::vector<std::string> sakora::VMCode::getArgs() {
    return args;
}

// 获取指定位置参数
// Get argument at specified position
std::string sakora::VMCode::getArg(int pos) {
    if (pos < static_cast<int>(args.size()))
        return args.at(pos);
    else
        throw std::out_of_range("Argument position out of range");
}

std::string sakora::VMCode::toString() {
    std::ostringstream oss;
    switch (VMOp) {
        case PUSH: oss << "PUSH"; break;
        case ADD: oss << "ADD"; break;
        case SUB: oss << "SUB"; break;
        case MUL: oss << "MUL"; break;
        case DIV: oss << "DIV"; break;
        case LGC_AND: oss << "LGC_AND"; break;
        case LGC_OR: oss << "LGC_OR"; break;
        case LGC_NOT_EQU: oss << "LGC_NOT_EQU"; break;
        case LGC_EQU: oss << "LGC_EQU"; break;
        case LGC_MR_THAN: oss << "LGC_MR_THAN"; break;
        case LGC_LS_THAN: oss << "LGC_LS_THAN"; break;
        case LGC_MREQU_THAN: oss << "LGC_MREQU_THAN"; break;
        case LGC_LSEQU_THAN: oss << "LGC_LSEQU_THAN"; break;
        case LGC_NOT: oss << "LGC_NOT"; break;
        case ARR_MAKE: oss << "ARR_MAKE"; break;
        case ARR_TIDY_CHK: oss << "ARR_TIDY_CHK"; break;
        case DECLARE: oss << "DECLARE"; break;
        case ASSIGN: oss << "ASSIGN"; break;
        case GET: oss << "GET"; break;
        case FROM: oss << "FROM"; break;
        case BLOCK_START: oss << "BLOCK_START"; break;
        case BLOCK_END: oss << "BLOCK_END"; break;
        case FLAG: oss << "FLAG"; break;
        case JTIN: oss << "JTIN"; break;
        case JTBCK: oss << "JTBCK"; break;
        case JFLGIN: oss << "JFLGIN"; break;
        case JNOFLG_IN: oss << "JNOFLG_IN"; break;
    }
    oss << " ";
    for (size_t i = 0; i < args.size(); ++i) {
        oss << args[i];
        if (i < args.size() - 1) oss << " ";
    }
    return oss.str();
}



sakora::VMCode sakora::CodeMaker::push(std::string value, std::string arg, int ln, int col) {
return VMCode(sakora::PUSH, ln, col, {value, arg});
}

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
sakora::VMCode sakora::CodeMaker::jflgin(std::string target_flag) {
    return VMCode(sakora::JFLGIN, 0, 0, {target_flag});
}
sakora::VMCode sakora::CodeMaker::jnoflg_in(std::string target_flag) {
    return VMCode(sakora::JNOFLG_IN, 0, 0, {target_flag});
}
