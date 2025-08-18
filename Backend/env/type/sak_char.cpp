#include "sak_char.h"

sakType::sakChar::sakChar(const char v) : val(v) {}

const char& sakType::sakChar::getVal() { return val; }
bool sakType::sakChar::setVal(const char nv) { val = nv; return true; }