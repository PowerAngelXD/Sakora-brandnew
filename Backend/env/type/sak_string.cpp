#include "sak_string.h"


sakType::sakString::sakString(const std::string&& v) : val(v) {}
sakType::sakString::sakString(const std::string& v) : val(v) {}

const std::string& sakType::sakString::getVal() { return val; }
bool sakType::sakString::setVal(const std::string& nv) { val = nv; return true; }
