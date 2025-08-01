#ifndef SAKORA_SAK_INT_H
#define SAKORA_SAK_INT_H

#include "sak_basic.h"

namespace sakType {
    class sakInt : public sakBasicType {
        int val;
    public:
        sakInt(int&& v);
        sakInt(int& v);
        const int& getVal();
        bool setVal(int& nv);
    };
}

#endif