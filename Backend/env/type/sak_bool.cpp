#include "sak_bool.h"

namespace sakType {
    sakBool::sakBool(bool&& v) : val(v) {}
    sakBool::sakBool(bool& v) : val(v) {}
    
    const bool& sakBool::getVal() { return val; }
    bool sakBool::setVal(bool& nv) { val = nv; return true; }
}
