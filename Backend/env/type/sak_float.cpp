#pragma GCC optimize(3,"Ofast","inline")
#include "sak_float.h"

sakType::sakFloat::sakFloat(double&& v) : val(v) {}
sakType::sakFloat::sakFloat(double& v) : val(v) {}

const double& sakType::sakFloat::getVal() { return val; }
bool sakType::sakFloat::setVal(double& nv) { val = nv; return true; }
