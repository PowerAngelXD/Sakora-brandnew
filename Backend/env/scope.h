#ifndef SAKORA_SCOPE_H
#define SAKORA_SCOPE_H

#include "object.h"
#include <algorithm>
#include <list>

class sakScope {
    std::vector<Object> objs;
    std::string scopeName;
public:
    sakScope()=default;
    sakScope(std::string name, std::initializer_list<Object> list);
    sakScope(std::string name);
    ~sakScope();

    bool hasObj(std::string n);
    Object& getObj(std::string n, int ln, int col);
    sakScope& addObj(Object obj);
    void assign(Object obj); // 用来更新现有的Object状态
};

// 管理Scope用的类
class sakScopeMgr {
    std::list<sakScope> scopePool; // 储存scope的地方，表示scope的上下级关系
    std::shared_ptr<sakScope> currentScope = nullptr; // 当前所在scope
public:
    sakScopeMgr();

    bool hasObject(std::string n);
    std::shared_ptr<sakScope> getCurrent();

    Object getObject(std::string n, int ln, int col);
    sakScopeMgr& createObject(Object obj);
    void assignObject(Object obj);

    void createScope(std::string name = "[Tag=Default Scope]");
    void deleteCurrent();
};

#endif