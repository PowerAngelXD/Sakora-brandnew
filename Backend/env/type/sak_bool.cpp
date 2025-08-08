#include "sak_bool.h"

sakType::sakBool::sakBool(bool&& v) : val(v) {}
sakType::sakBool::sakBool(bool& v) : val(v) {}

const bool& sakType::sakBool::getVal() { return val; }
bool sakType::sakBool::setVal(bool& nv) { val = nv; return true; }
