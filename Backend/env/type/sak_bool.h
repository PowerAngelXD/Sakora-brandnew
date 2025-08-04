#ifndef SAKORA_SAK_BOOL_H
#define SAKORA_SAK_BOOL_H

#include "sak_basic.h"

namespace sakType {
    class sakBool : public sakBasicType {
        bool val;
    public:
        sakBool(bool&& v);
        sakBool(bool& v);
        const bool& getVal();
        bool setVal(bool& nv);
    };
}

#endif