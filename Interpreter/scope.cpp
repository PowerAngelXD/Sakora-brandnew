#include "scope.h"

bool sakora::Scope::isExist(std::string field) {
    if (members.find(field) != members.end()) {
        return true;
    }
    else {
        if (prev.expired()) {
            return this->prev.lock()->isExist(field);
        }
        else return false;
    }
}

std::shared_ptr<sakora::Scope> sakora::Scope::locate(std::string field, int ln, int col) {
    if (members.find(field) != members.end()) {
        return shared_from_this();
    }
    else {
        if (prev.expired()) {
            return this->prev.lock()->locate(field, ln, col);
        }
        else throw VMError::UnknownIdentifierError(field, ln, col);
    }
}

// Scope Manager

sakora::ScopeManager::ScopeManager() {
    currentScope = std::make_shared<Scope>();
    globalScope = *currentScope;
}

void sakora::ScopeManager::createScope() {
    auto newScope = std::make_shared<Scope>();
    newScope->prev = currentScope;
    currentScope->next = newScope;
    currentScope = newScope;
}
void sakora::ScopeManager::removeScope() {
    std::shared_ptr<Scope> prevScope = currentScope->prev.lock();
    
    if (prevScope) {
        currentScope = prevScope;
        currentScope->next = nullptr;
    }
}

sakora::Value& sakora::ScopeManager::get(std::string field, int ln, int col) {
    return currentScope->locate(field, ln, col)->members[field];
}