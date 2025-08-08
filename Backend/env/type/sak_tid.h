#ifndef SAKORA_SAK_TID_H
#define SAKORA_SAK_TID_H

#include <memory>
#include "sak_basic.h"

namespace sakType {
    enum class Type {
        Int, String, Float, Boolean, Tid, Null
    };

    struct ArrayModifider {
        int length = 0;    // Array长度
        int dimension = 1; // 数组维度
    };

    struct TypeModifier {
        std::shared_ptr<ArrayModifider> arrayMod = nullptr;
    };

    class sakTid : public sakBasicType {
        Type mainType;           // 主要类型，标识一个tid的主要类型，举个例子，如果有array的修饰符，那么主要类型就是array的元素类型
                                 // 如果有fn的修饰符，那么主要类型就是函数的返回值类型
        TypeModifier modifier;
    public:
        sakTid(const Type&& v);
        sakTid(const Type& v);
        sakTid(const Type&& v, ArrayModifider am);
        sakTid(const Type& v, ArrayModifider am);
        const Type& getVal();
        const TypeModifier& getModifier();
        bool setVal(const Type& nv);
        bool setModifier(const ArrayModifider& arrayMod);
    };
}

#endif