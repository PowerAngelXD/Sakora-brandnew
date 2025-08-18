#ifndef SAKORA_SAK_CHAR_H
#define SAKORA_SAK_CHAR_H

#include "sak_basic.h"

namespace sakType {
    class sakChar : public sakBasicType {
        char val;
    public:
        sakChar(const char v);
        const char& getVal();
        bool setVal(const char nv);
    };
}

#endif