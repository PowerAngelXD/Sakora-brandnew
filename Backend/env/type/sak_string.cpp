#include "sak_string.h"

namespace sakType {
    sakString::sakString(const std::string&& v) : val(v) {}
    sakString::sakString(const std::string& v) : val(v) {}

    const std::string& sakString::getVal() { return val; }
    bool sakString::setVal(const std::string& nv) { val = nv; return true; }
}
