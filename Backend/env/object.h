#ifndef SAKORA_OBJECT_H
#define SAKORA_OBJECT_H
#include "value.h"
#include "../ins.h"
#include <map>
#include <vector>
#include <string>
#include <list>

using sakFnArgsList = std::map<std::string, sakType::sakTid>;

class Object;

// 所有sakoraObject的基类
class ObjectBase {
protected:
    std::string objName; // Object的名称，也可以看作标识符（Identifier）
    int defLine, defColumn; // 定义Object所在的位置
public:
    virtual const std::string& getName();
};

// 仅储存值的Object
class ValueObject : public ObjectBase{
    std::shared_ptr<sakValue> value = nullptr;
    sakType::sakTid type;
public:
    ValueObject(std::string name, sakValue val, int ln, int col);
    ValueObject(std::string name, sakValue val, sakType::sakTid tid, int ln, int col);
    ValueObject(std::string name, sakType::sakTid tid, int ln, int col);

    bool isNull();
    sakValue& getValue();
    ValueObject& assign(sakValue value);
};

// 储存函数的Object
class FuncObject : public ObjectBase{
    sakFnArgsList fnArgs; // 函数的参数列表，前面为参数名，后面为参数对应类型
    std::vector<INS::Instruction> fnBody;          // 函数体
    sakType::sakTid fnReturnType;                  // 函数返回类型
public:
    FuncObject(std::string n, sakFnArgsList args, std::vector<INS::Instruction> bdy, sakType::sakTid retType, int ln, int col);

    sakFnArgsList& getArgs();
    std::vector<INS::Instruction>& getBody();
    const sakType::sakTid& getReturnType();
};

// 储存结构体的Object
class StructObject : public ObjectBase {
    std::vector<std::shared_ptr<ValueObject>> members;
public:
    StructObject(std::string n, std::vector<ValueObject> mems, int ln, int col);

    bool hasMember(std::string n);
    ValueObject& getMember(std::string n);
};

// 储存自定义类的Object
class CustomTypeObject : public ObjectBase {
    std::vector<std::shared_ptr<Object>> members;
public:
    CustomTypeObject(std::string n, std::vector<std::shared_ptr<Object>> mems, int ln, int col);

    bool hasMember(std::string n);
    Object& getObject(std::string n);
};

// Object类，储存所有已有的Object
class Object : public ObjectBase{
    std::variant<ValueObject, FuncObject, CustomTypeObject, StructObject> object;
public:
    Object(std::string n, ValueObject valObj, int ln, int col);
    Object(std::string n, FuncObject fnObj, int ln, int col);
    Object(std::string n, StructObject stctObj, int ln, int col);
    Object(std::string n, CustomTypeObject cttObj, int ln, int col);

    Object(std::string n, sakValue value, sakType::sakTid tid, int ln, int col);
    Object(std::string n, sakType::sakTid tid, int ln, int col);
    Object(std::string n, sakValue value, int ln, int col);

    ~Object();

    bool isValueObj();
    bool isFnObj();
    bool isCustomTypeObj();
    bool isStructObj();

    ValueObject& getValueObj();
    FuncObject& getFnObj();
    CustomTypeObject& getCustomTypeObj();
    StructObject& getStructObj();

    const int& getLine();
    const int& getColumn();
};

#endif