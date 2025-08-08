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
const sakType::Type& sakType::sakTid::getVal() { return mainType; }
bool sakType::sakTid::setVal(const Type& nv) { mainType = nv; return true; }
bool sakType::sakTid::setModifier(const ArrayModifider& arrayMod) {
    modifier.arrayMod = std::make_shared<ArrayModifider>(arrayMod);
    return true;
}

