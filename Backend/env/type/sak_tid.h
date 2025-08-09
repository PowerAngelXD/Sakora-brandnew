#ifndef SAKORA_SAK_TID_H
#define SAKORA_SAK_TID_H

#include <memory>
#include <vector>
#include "sak_basic.h"

namespace sakType {
    // 表明Sakora的基本类型
    // 需要注意的是，EMPTY类型是用来标注一个sakTid不存在mainType的，此时就只需要TypeModifier了
    enum class Type {
        Int, String, Float, Boolean, Tid, Null, EMPTY
    };

    struct ArrayModifider {
        Type arrayType = Type::Null; // 数组类型

        std::vector<int> lengths; // 各维度数组的长度
        int dimension = 1; // 数组维度
    };

    struct TypeModifier {
        std::shared_ptr<ArrayModifider> arrayMod = nullptr;
    };

    class sakTid : public sakBasicType {
        Type mainType;

        TypeModifier modifier;
    public:
        sakTid()=default;

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