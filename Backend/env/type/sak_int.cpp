#pragma GCC optimize(3,"Ofast","inline")
#include "sak_int.h"


sakType::sakInt::sakInt(int&& v) : val(v) {}
sakType::sakInt::sakInt(int& v) : val(v) {}

const int& sakType::sakInt::getVal() { return val; }
bool sakType::sakInt::setVal(int& nv) { val = nv; return true; }

