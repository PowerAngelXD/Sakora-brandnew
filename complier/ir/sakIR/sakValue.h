#ifndef SAKORA_SAKVALUE_H
#define SAKORA_SAKVALUE_H

#include <iostream>
#include <variant>

#include "sakType.h"

namespace sakIR {
    // Value for IROpcode
    class Value {
        std::variant<int, double, std::string, char, bool, std::nullptr_t> content;

    public:
        Value(int iv);
        Value(double dbv);
        Value(std::string strv);
        Value(bool bv);
        Value();

        BasicType getType();

        int unboxInt();
        double unboxFloat();
        std::string unboxStr();
        char unboxChar();
        bool unboxBool();
        std::nullptr_t unboxNull();
    };
}

#endif