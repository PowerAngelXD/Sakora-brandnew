#pragma GCC optimize(3,"Ofast","inline")
#include "scope.h"

bool sakora::Scope::isExist(std::string field) {
    return members.find(field) != members.end();
}

// Scope Manager

sakora::ScopeManager::ScopeManager() {
   scopeStorage.push_back(Scope());
}

void sakora::ScopeManager::createScope() {
    scopeStorage.push_back(Scope());
}

void sakora::ScopeManager::removeScope() {
    if (scopeStorage.size() != 1) scopeStorage.pop_back();
}

sakora::Value& sakora::ScopeManager::get(std::string field, int ln, int col) {
    if (!isExist(field))
        throw VMError::UnknownIdentifierError(field, ln, col);
    for (std::size_t i = scopeStorage.size(); i > 0; i --) {
        for (auto member : scopeStorage.at(i - 1).members) {
            if (member.first == field) return scopeStorage.at(i - 1).members[field];
        }
    }

    throw VMError::UnknownIdentifierError(field, ln, col);
}

sakora::Scope& sakora::ScopeManager::getCurrent() {
    return scopeStorage.at(scopeStorage.size() - 1);
}

sakora::Scope& sakora::ScopeManager::getGlobal() {
    return scopeStorage.at(0);
}

bool sakora::ScopeManager::isExist(std::string field) {
    for (std::size_t i = scopeStorage.size(); i > 0; i --) {
        for (auto member : scopeStorage.at(i - 1).members) {
            if (member.first == field) return true;
        }
    }
    
    return false;
}

void sakora::ScopeManager::declare(std::string name, sakora::Value val) {
    if (isExist(name))
        throw VMError::AlreadyIdentifierError(name, val.line, val.column);
    getCurrent().members[name] = val;
}