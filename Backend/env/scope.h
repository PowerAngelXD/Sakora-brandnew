#ifndef SAKORA_SCOPE_H
#define SAKORA_SCOPE_H

#include "object.h"
#include <algorithm>

class sakScope {
    std::vector<Object> objs;
    std::vector<std::shared_ptr<sakScope>> scopes;
    std::string scopeName;
public:
    sakScope()=default;
    sakScope(std::string name, std::initializer_list<Object> list);
    sakScope(std::string name);
    ~sakScope();

    bool hasObj(std::string n);
    Object& getObj(std::string n, int ln, int col);
    sakScope& addObj(Object obj);
    void update(Object obj); // 用来更新现有的Object状态

    bool hasScope(std::string n);
    sakScope& getScope(std::string n);
    sakScope& addScope(std::string n, std::initializer_list<Object> list);
    sakScope& createScope(std::string n);
};

#endif