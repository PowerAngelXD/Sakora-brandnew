#include "instruction.h"

// 构造函数实现
// Constructor implementation
sakora::sakIns::sakIns(sakora::InsOp op, int ln, int col, std::initializer_list<std::string> _args)
    : VMOp(op), line(ln), column(col), args(_args) {}

// 获取指令操作码
// Get instruction opcode
const sakora::InsOp& sakora::sakIns::getOp() {
    return VMOp;
}

// 获取所有参数
// Get all arguments
std::vector<std::string> sakora::sakIns::getArgs() {
    return args;
}

// 获取指定位置参数
// Get argument at specified position
std::string sakora::sakIns::getArg(int pos) {
    if (pos < static_cast<int>(args.size()))
        return args[pos];
    return "";
}

std::string sakora::sakIns::toString() {
    std::ostringstream oss;
    oss << "Instruction(Op: ";
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
        case NEW_SCOPE: oss << "NEW_SCOPE"; break;
        case END_SCOPE: oss << "END_SCOPE"; break;
        case FLAG: oss << "FLAG"; break;
        case JTIN: oss << "JTIN"; break;
        case JTBCK: oss << "JTBCK"; break;
        case JOUT: oss << "JOUT"; break;
    }
    oss << ", Line: " << line << ", Column: " << column << ", Args: [";
    for (size_t i = 0; i < args.size(); ++i) {
        oss << args[i];
        if (i < args.size() - 1) oss << ", ";
    }
    oss << "])";
    return oss.str();
}
