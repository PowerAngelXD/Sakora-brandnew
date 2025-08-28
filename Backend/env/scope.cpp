#pragma GCC optimize(3,"Ofast","inline")
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

void sakScope::assign(Object obj) {
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

// Scope Manager

sakScopeMgr::sakScopeMgr() {
    this->scopePool.emplace_back("__global__"); // 放入初始的global作用域
    this->currentScope = std::make_shared<sakScope>(this->scopePool.back());
}

bool sakScopeMgr::hasObject(std::string n) {
    if (currentScope->hasObj(n)) return true;
    else {
        for (auto scope : this->scopePool) {
            if (scope.hasObj(n)) return  true;
        }
        return false;
    }
}
std::shared_ptr<sakScope> sakScopeMgr::getCurrent() {
    return this->currentScope;
}

Object sakScopeMgr::getObject(std::string n, int ln, int col) {
    if (currentScope->hasObj(n)) {
        return currentScope->getObj(n, ln, col);
    }
    else {
        for (auto& scope : this->scopePool) {
            if (scope.hasObj(n)) return scope.getObj(n, ln, col);
        }
        throw VMError::UnknownIdentifierError(n, ln, col);
    }
}
sakScopeMgr& sakScopeMgr::createObject(Object obj) {
    currentScope->addObj(obj);
    this->scopePool.back() = *currentScope;

    return *this;
}
void sakScopeMgr::assignObject(Object obj) {
    if (currentScope->hasObj(obj.getName())) {
        currentScope->assign(obj);
        this->scopePool.back() = *currentScope;
    }
    else {
        for (auto& scope : this->scopePool) {
            if (scope.hasObj(obj.getName())) scope.assign(obj);
        }
    }
}
void sakScopeMgr::createScope(std::string name) {
    this->scopePool.emplace_back(name);
    currentScope = std::make_shared<sakScope>(this->scopePool.back());
}
void sakScopeMgr::deleteCurrent() {
    this->scopePool.pop_back();
    currentScope = std::make_shared<sakScope>(this->scopePool.back());
}