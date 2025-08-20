#ifndef SAKORA_IDENTIFIER_H
#define SAKORA_IDENTIFIER_H

#include "value.h"

class sakId {
    std::shared_ptr<sakValue> value = nullptr;
    sakType::sakTid idType;
    std::string id;
    int refCount = 0;
public:
    sakId(std::string i, sakValue val);
    sakId(std::string i, sakType::sakTid tid);
    sakId(std::string i, sakType::sakTid tid, sakValue val);
    
    const std::string& getId();
    const sakValue& getVal();
    sakId& writeVal(sakValue val);

};

#endif