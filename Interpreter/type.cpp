#include "type.h"

sakora::TypeId::TypeId(BasicType t) : bType(t), arrMod(nullptr) {}
sakora::TypeId::TypeId(BasicType t, int length) : bType(t) {
    arrMod = std::make_shared<ArrayModifier>();
    arrMod->dimension = 1;
    arrMod->lengthList.push_back(length);
}
sakora::TypeId::TypeId(BasicType t, int ds, std::initializer_list<int> llist) : bType(t) {
    arrMod = std::make_shared<ArrayModifier>();
    arrMod->dimension = ds;
    arrMod->lengthList = llist;
}
sakora::TypeId::TypeId(BasicType t, ArrayModifier amdr) : bType(t) {
    arrMod = std::make_shared<ArrayModifier>(amdr);
}

const sakora::BasicType& sakora::TypeId::getBasicType() {
    return bType;
}   

const sakora::ArrayModifier& sakora::TypeId::getArrMod() {
    return *arrMod;
}

std::string sakora::TypeId::toString() {
    std::string res;
    switch (bType) {
        case Int: res = "Int"; break;
        case Float: res = "Float"; break;
        case String: res = "String"; break;
        case Char: res = "Char"; break;
        case Bool: res = "Bool"; break;
        case Null: res = "Null"; break;
        case Custom: res = "Custom"; break;
    }
    if (arrMod != nullptr) {
        res += "[";
        for (size_t i = 0; i < arrMod->lengthList.size(); ++i) {
            res += std::to_string(arrMod->lengthList[i]);
            if (i != arrMod->lengthList.size() - 1)
                res += ",";
        }
        res += "]";
    }
    return res;
}   