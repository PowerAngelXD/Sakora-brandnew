#ifndef SAKORA_SAK_TID_H
#define SAKORA_SAK_TID_H

#include "sak_basic.h"

namespace sakType {
    enum class Type {
        Int, String, Float, Boolean, Tid
    };

    class sakTid : public sakBasicType {
        Type val;
    public:
        sakTid(const Type&& v);
        sakTid(const Type& v);
        const Type& getVal();
        bool setVal(const Type& nv);
    };
}

#endif