#include "scope.h"

sakScope::sakScope(std::string name, std::initializer_list<sakId> list) 
    : ids(list), scopeName(std::move(name)) {
}

bool sakScope::hasId(std::string n) {
    return std::find_if(ids.begin(), ids.end(), 
                       [&n](sakId& id) { 
                           return id.getId() == n; 
                       }) != ids.end();
}

sakId& sakScope::getId(std::string n, int ln, int col) {
    auto it = std::find_if(ids.begin(), ids.end(), 
                          [&n](sakId& id) { 
                              return id.getId() == n; 
                          });
    
    if (it != ids.end()) {
        return *it;
    }

    throw VMError::UnknownIdentifierError(n, ln, col);
}

sakScope& sakScope::addId(sakId id) {
    if (hasId(id.getId()))
        throw VMError::AlreadyIdentifierError(id.getId(), id.getVal().defLine, id.getVal().defColumn);

    ids.push_back(std::move(id));
    return *this;
}

bool sakScope::hasScope(std::string n) {
    return std::find_if(scopes.begin(), scopes.end(), 
                       [&n](const std::shared_ptr<sakScope>& scope) { 
                           return scope->scopeName == n; 
                       }) != scopes.end();
}

sakScope& sakScope::getScope(std::string n) {
    auto it = std::find_if(scopes.begin(), scopes.end(), 
                          [&n](const std::shared_ptr<sakScope>& scope) { 
                              return scope->scopeName == n; 
                          });
    
    if (it != scopes.end()) {
        return **it;
    }
    
    throw std::runtime_error("Cannot find scope: " + n);
}

sakScope& sakScope::addScope(std::string n, std::initializer_list<sakId> list) {
    auto newScope = std::make_shared<sakScope>(std::move(n), list);
    scopes.push_back(newScope);
    return *newScope;
}