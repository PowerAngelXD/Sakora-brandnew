#ifndef SAKORA_INSTRUCTION_H
#define SAKORA_INSTRUCTION_H

#include <iostream>
#include <sstream>
#include <vector>

namespace sakora {
    // VM的操作指令
    enum InsOp {
        PUSH, 
        ADD, SUB, MUL, DIV, 
        LGC_AND, LGC_OR, LGC_NOT_EQU, LGC_EQU, LGC_MR_THAN, LGC_LS_THAN, LGC_MREQU_THAN, LGC_LSEQU_THAN, LGC_NOT,
        ARR_MAKE, ARR_TIDY_CHK, 
        DECLARE, ASSIGN, GET, FROM, 
        NEW_SCOPE, END_SCOPE, 
        FLAG, JTIN, JTBCK
    };

    // 指令类，管理指令使用
    class VMCode {
        InsOp VMOp;
        std::vector<std::string> args;
    public:
        int line, column;

        /* 构造函数，用于构造一个sakVM指令实例
           op       意指对应的VM指令
           ln, col  意指对应的行列
           args     意指参数
        */
        VMCode(InsOp op, int ln, int col, std::initializer_list<std::string> _args = {});

        const InsOp& getOp();
        std::vector<std::string> getArgs();
        std::string getArg(int pos = 0);

        std::string toString();
    };
}

#endif