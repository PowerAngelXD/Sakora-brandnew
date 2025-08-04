#include "sak_int.h"

namespace sakType {
    sakInt::sakInt(int&& v) : val(v) {}
    sakInt::sakInt(int& v) : val(v) {}

    const int& sakInt::getVal() { return val; }
    bool sakInt::setVal(int& nv) { val = nv; return true; }
}
