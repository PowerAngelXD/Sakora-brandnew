#ifndef SAKORA_SAK_FLOAT_H
#define SAKORA_SAK_FLOAT_H

#include "sak_basic.h"

namespace sakType {
    class sakFloat : public sakBasicType {
        double val;
    public:
        sakFloat(double&& v);
        sakFloat(double& v);
        const double& getVal();
        bool setVal(double& nv);
    };
}

#endif
