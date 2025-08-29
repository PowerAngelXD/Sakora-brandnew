#ifndef SAKORA_TYPE_H
#define SAKORA_TYPE_H

#include <iostream>
#include <vector>
#include <memory>

namespace sakora {
    // 表示sakora的基础类型
    enum BasicType { Int, Float, String, Char, Bool, Null, Custom };

    struct ArrayModifier {
        int dimension = 0; // 数组维度
        std::vector<int> lengthList; // 各个维度的数组长度
    };

    class TypeId {
        BasicType bType;   //  基础类型

        std::shared_ptr<ArrayModifier> arrMod = nullptr; // 结构修饰符：数组
    public:
        TypeId(BasicType t);
        TypeId(BasicType t, int length);
        TypeId(BasicType t, int ds, std::initializer_list<int> llist);
        TypeId(BasicType t, ArrayModifier amdr);

        const BasicType& getBasicType();
        const ArrayModifier& getArrMod();

        std::string toString();
    };
}

#endif