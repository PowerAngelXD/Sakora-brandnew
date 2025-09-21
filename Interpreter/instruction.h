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
        BLOCK_START, BLOCK_END, 
        FLAG, JTIN, JTBCK, JFLGIN, JNOFLG_IN
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

    using CodeSequence = std::vector<VMCode>;

    class CodeArgs {
    public:
        class Push {
        public:
           inline static std::string IDEN = "[IDEN]";
           inline static std::string TYPE = "[TYPE]"; 
           inline static std::string VAL = "[VAL]";
           inline static std::string FLAG = "[FLAG]";
        };

        class Declare {
        public:
            inline static std::string HAS_TMOD = "[HAS_TMOD]";
            inline static std::string NO_TMOD = "[NO_TMOD]";
        };

        class From {
        public:
            inline static std::string INDEX = "[INDEX]";
            inline static std::string MEMBER = "[MEMBER]";
        };
    };

    class VMFlags {
    public:
        inline static std::string CONTROL_FLOW_OVER = "[CONTROL_FLOW_OVER]";
    };

    class CodeMaker {
    public:
        static VMCode push(std::string value, std::string arg, int ln, int col);
        static VMCode add();
        static VMCode sub();
        static VMCode mul();
        static VMCode div();
        static VMCode lgcAnd();
        static VMCode lgcOr();
        static VMCode lgcNotEqu();
        static VMCode lgcEqu();
        static VMCode lgcMrThan();
        static VMCode lgcLsThan();
        static VMCode lgcMrEquThan();
        static VMCode lgcLsEquThan();
        static VMCode lgcNot();
        static VMCode arrMake(std::string size, int ln, int col);
        static VMCode arrTidyChk(int ln, int col);
        static VMCode declare(std::string name, std::string hasMod, int ln, int col);
        static VMCode assign(int ln, int col);
        static VMCode get(std::string name, int ln, int col);
        static VMCode from(std::string type, int ln, int col);
        static VMCode blockStart();
        static VMCode blockEnd();
        static VMCode flag(std::string flag_name);
        static VMCode jtin();
        static VMCode jtbck();
        static VMCode jflgin(std::string target_flag);
        static VMCode jnoflg_in(std::string target_flag);
    };
}

#endif