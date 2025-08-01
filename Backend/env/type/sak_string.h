#ifndef SAKORA_SAK_STRING_H
#define SAKORA_SAK_STRING_H

#include "sak_basic.h"
#include <string>

namespace sakType {
    class sakString : public sakBasicType {
        std::string val;
    public:
        sakString(const std::string&& v);
        sakString(const std::string& v);
        const std::string& getVal();
        bool setVal(const std::string& nv);
    };
}

#endif
