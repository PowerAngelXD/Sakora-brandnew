#ifndef SAKORA_SCOPE_H
#define SAKORA_SCOPE_H

#include "value.h"
#include "../Error/VMError.h"
#include <iostream>
#include <map>

namespace sakora {
    class Scope : public std::enable_shared_from_this<Scope> {
    public:
        std::weak_ptr<Scope> prev; // 指针，指向上一个scope
        std::shared_ptr<Scope> next = nullptr; // 指针，指向下一个scope

        std::map<std::string, Value> members;

        Scope()=default;

        bool isExist(std::string field);
        std::shared_ptr<Scope> locate(std::string field, int ln, int col);
    };

    class ScopeManager {
    public:
        Scope globalScope;
        std::shared_ptr<Scope> currentScope;

        ScopeManager();

        void createScope();
        void removeScope();
    };
}

#endif