#include "scope.h"

sakScope::sakScope(std::string name, std::initializer_list<Object> list) 
    : objs(list), scopeName(std::move(name)) {}
sakScope::sakScope(std::string name) {
    scopeName = std::move(name);
}
sakScope::~sakScope() {
    for (auto obj : objs) {
        obj.~Object();
    }
    for (auto scope : scopes) {
        scope->~sakScope();
    }
}
bool sakScope::hasObj(std::string n) {
    return std::find_if(objs.begin(), objs.end(), 
                       [&n](Object& obj) { 
                           return obj.getName() == n; 
                       }) != objs.end();
}

Object& sakScope::getObj(std::string n, int ln, int col) {
    auto it = std::find_if(objs.begin(), objs.end(), 
                          [&n](Object& obj) { 
                              return obj.getName() == n; 
                          });
    
    if (it != objs.end()) {
        return *it;
    }

    throw VMError::UnknownIdentifierError(n, ln, col);
}

sakScope& sakScope::addObj(Object obj) {
    if (hasObj(obj.getName()))
        throw VMError::AlreadyIdentifierError(obj.getName(), obj.getLine(), obj.getColumn());

    objs.push_back(std::move(obj));
    return *this;
}

void sakScope::update(Object obj) {
    if (!hasObj(obj.getName())) 
        throw VMError::UnknownIdentifierError(obj.getName(), obj.getLine(), obj.getColumn());

    auto n = obj.getName();
    auto it = std::find_if(objs.begin(), objs.end(), 
                          [&n](Object& _obj) { 
                              return _obj.getName() == n; 
                          });
    
    objs.erase(it);
    objs.push_back(obj);
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

sakScope& sakScope::addScope(std::string n, std::initializer_list<Object> list) {
    auto newScope = std::make_shared<sakScope>(std::move(n), list);
    scopes.push_back(newScope);
    return *newScope;
}

sakScope& sakScope::createScope(std::string n) {
    auto newScope = std::make_shared<sakScope>(std::move(n));
    scopes.push_back(newScope);
    return *newScope;
}