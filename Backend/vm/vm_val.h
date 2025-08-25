#ifndef SAKORA_VM_VAL_H
#define SAKORA_VM_VAL_H

#include "../env/scope.h"

class VMVal {
    std::variant<sakValue, Object, sakScope> instance;

public:
    VMVal(sakValue sak_val);
    VMVal(Object sak_obj);
    VMVal(sakScope sak_scope);

    bool isValue();
    bool isObj();
    bool isScope();

    sakValue getValue();
    Object& getObj();
    sakScope& getScope();
};

#endif