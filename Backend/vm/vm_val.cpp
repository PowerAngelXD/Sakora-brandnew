#include "vm_val.h"
#include <stdexcept>

VMVal::VMVal(sakValue sak_val) : instance(std::move(sak_val)) {}
VMVal::VMVal(Object sak_obj) : instance(std::move(sak_obj)) {}
VMVal::VMVal(sakScope sak_scope) : instance(std::move(sak_scope)) {}

bool VMVal::isValue() {
    return std::holds_alternative<sakValue>(instance);
}

bool VMVal::isObj() {
    return std::holds_alternative<Object>(instance);
}

bool VMVal::isScope() {
    return std::holds_alternative<sakScope>(instance);
}

sakValue VMVal::getValue() {
    if (isObj()) return std::get<Object>(instance).getValueObj().getValue();
    else if (isValue()) return std::get<sakValue>(instance);
    else throw std::bad_variant_access();
}

Object& VMVal::getObj() {
    if (!isObj()) throw std::bad_variant_access();
    return std::get<Object>(instance);
}

sakScope& VMVal::getScope() {
    if (!isScope()) throw std::bad_variant_access();
    return std::get<sakScope>(instance);
}
