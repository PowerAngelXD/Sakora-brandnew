#ifndef SAKORA_VISITOR_H
#define SAKORA_VISITOR_H

#include "../Frontend/Parser/parser.h"
#include "instruction.h"

namespace sakora {
    using CodeSequence = std::vector<VMCode>;

    class CodeMaker {
    public:
        static VMCode PUSH(std::string value, int ln, int col);
        static VMCode ADD();
        static VMCode SUB();
        static VMCode MUL();
        static VMCode DIV();
        static VMCode LGC_AND();
        static VMCode LGC_OR();
        static VMCode LGC_NOT_EQU();
        static VMCode LGC_EQU();
        static VMCode LGC_MR_THAN();
        static VMCode LGC_LS_THAN();
        static VMCode LGC_MREQU_THAN();
        static VMCode LGC_LSEQU_THAN();
        static VMCode LGC_NOT();
        static VMCode ARR_MAKE(std::string size, int ln, int col);
        static VMCode ARR_TIDY_CHK(int ln, int col);
        static VMCode DECLARE(std::string name, int ln, int col);
        static VMCode ASSIGN(std::string name, int ln, int col);
        static VMCode GET(std::string name, int ln, int col);
        static VMCode FROM(std::string type, int ln, int col);
        static VMCode NEW_SCOPE();
        static VMCode END_SCOPE();
        static VMCode FLAG(std::string flag_name);
        static VMCode JTIN();
        static VMCode JTBCK();
    };

    class Visitor {
    public:
        CodeSequence seq;

        void make(VMCode code);

        
    };
}

#endif