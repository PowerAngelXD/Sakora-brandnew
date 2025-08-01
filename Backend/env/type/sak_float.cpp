#include "sak_float.h"

namespace sakType {
    sakFloat::sakFloat(double&& v) : val(v) {}
    sakFloat::sakFloat(double& v) : val(v) {}

    const double& sakFloat::getVal() {
        return val;
    }

    bool sakFloat::setVal(double& nv) {
        val = nv;
        return true;
    }
}
