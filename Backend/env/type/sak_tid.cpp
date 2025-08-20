#include "sak_tid.h"


sakType::sakTid::sakTid(const Type&& v) : mainType(v) {}
sakType::sakTid::sakTid(const Type& v) : mainType(v) {}
sakType::sakTid::sakTid(const Type&& v, ArrayModifider am) : mainType(v) {
    modifier.arrayMod = std::make_shared<ArrayModifider>(am);
}

sakType::sakTid::sakTid(const Type& v, ArrayModifider am) : mainType(v) {
    modifier.arrayMod = std::make_shared<ArrayModifider>(am);
}

const sakType::TypeModifier& sakType::sakTid::getModifier() {
    return modifier;
}
sakType::Type sakType::sakTid::getVal() { return mainType; }
bool sakType::sakTid::setVal(const Type& nv) { mainType = nv; return true; }
bool sakType::sakTid::setModifier(const ArrayModifider& arrayMod) {
    modifier.arrayMod = std::make_shared<ArrayModifider>(arrayMod);
    return true;
}

bool sakType::sakTid::operator ==(sakTid tid) {
    if ((this->mainType == tid.mainType) && (this->mainType != sakType::Type::EMPTY &&tid.mainType != sakType::Type::EMPTY)) return true;

    if (this->modifier.arrayMod) {
        if (!tid.modifier.arrayMod) return false;
        else if (this->modifier.arrayMod->arrayType != tid.modifier.arrayMod->arrayType)
            return false;
        else if (this->modifier.arrayMod->dimension != tid.modifier.arrayMod->dimension)
            return false;
        else if (this->modifier.arrayMod->lengths != tid.modifier.arrayMod->lengths)
            return false;
        else return true;
    }
    else return false;
}
bool sakType::sakTid::operator !=(sakTid tid) {
    return !this->operator==(tid);
}

