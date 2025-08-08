#include "sak_tid.h"

namespace sakType {
    sakTid::sakTid(const Type&& v) : val(v) {}
    sakTid::sakTid(const Type& v) : val(v) {}

    const Type& sakTid::getVal() { return val; }
    bool sakTid::setVal(const Type& nv) { val = nv; return true; }
}
