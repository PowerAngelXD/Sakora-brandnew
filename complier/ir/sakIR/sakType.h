#ifndef SAKORA_SAKTYPE_H
#define SAKORA_SAKTYPE_H

#include "includes/magic_enum.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

namespace sakIR {
    // Forward Declaration
    class ValueType;

    // Represents the basic type of sakora
    enum class BasicType { Int, Float, String, Char, Bool, Null };

    // Descriptors used to describe the array structure
    struct ArrayMod {
        std::vector<int> lengths; // array length within each dimension
        int dimension; // array dimension
    };

    // Descriptors used to describe the tuple structure
    struct TupleMod {
        std::vector<std::shared_ptr<ValueType>> memTypes; // 各成员type
    };

    // A collection of structure descriptors
    struct StructSet {
        std::shared_ptr<ArrayMod> arrMod = nullptr;
        std::shared_ptr<TupleMod> tupleMod = nullptr;

        // Has struct modifier
        bool hasMod();

        // Check is array modifier
        bool isArr();

        // Check is tuple modifier
        bool isTuple();
    };

    // Represents SakoraValue's Type
    struct ValueType {
        BasicType bType = BasicType::Null;
        StructSet stctMod;
    };
}

#endif