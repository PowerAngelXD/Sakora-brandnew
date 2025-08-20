#ifndef SAKORA_SCOPE_H
#define SAKORA_SCOPE_H

#include "identifier.h"
#include <algorithm>

class sakScope {
    std::vector<sakId> ids;
    std::vector<std::shared_ptr<sakScope>> scopes;
    std::string scopeName;
public:
    sakScope()=default;
    sakScope(std::string name, std::initializer_list<sakId> list);

    bool hasId(std::string n);
    sakId& getId(std::string n, int ln, int col);
    sakScope& addId(sakId id);

    bool hasScope(std::string n);
    sakScope& getScope(std::string n);
    sakScope& addScope(std::string n, std::initializer_list<sakId> list);
};

#endif