#include "scope.h"

bool sakora::Scope::isExist(std::string field) {
    return members.find(field) != members.end();
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