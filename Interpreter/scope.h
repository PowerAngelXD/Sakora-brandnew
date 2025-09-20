#ifndef SAKORA_SCOPE_H
#define SAKORA_SCOPE_H

#include "value.h"
#include "../Error/VMError.h"
#include <iostream>
#include <map>

namespace sakora {
    using memberPair = std::pair<std::string, Value>;
    class Scope{
    public:
        std::map<std::string, Value> members;

        Scope()=default;

        bool isExist(std::string field);
    };

    class ScopeManager {
    public:
        std::vector<Scope> scopeStorage;

        ScopeManager();

        Value& get(std::string field, int ln, int col);
        Scope& getCurrent();
        Scope& getGlobal();
        bool isExist(std::string field);

        void createScope();
        void removeScope();
        void declare(std::string name, Value val);
    };
}

#endif