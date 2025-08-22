#include "object.h"
#include "../ins.h"
#include "../../Error/VMError.h"
#include <stdexcept>

// ObjectBase
const std::string& ObjectBase::getName() {
    return objName;
}

// ValueObject
ValueObject::ValueObject(std::string name, sakValue val, int ln, int col) : value(std::make_shared<sakValue>(std::move(val))) {
    this->objName = std::move(name);
    this->type = this->value->inferType().getTidVal();
    this->defLine = ln;
    this->defColumn = col;
}

ValueObject::ValueObject(std::string name, sakValue val, sakType::sakTid tid, int ln, int col)
    : value(std::make_shared<sakValue>(std::move(val))), type(tid) {
    this->objName = std::move(name);
    this->defLine = ln;
    this->defColumn = col;
}

ValueObject::ValueObject(std::string name, sakType::sakTid tid, int ln, int col)
    : type(tid) {
    this->objName = std::move(name);
    this->defLine = ln;
    this->defColumn = col;
}

bool ValueObject::isNull() {
    return value == nullptr;
}

const sakValue& ValueObject::getValue() {
    if (this->isNull())
        throw VMError::UseNullValueError(defLine, defColumn);
    
    return *value;
}

ValueObject& ValueObject::assign(sakValue val) {
    if (this->isNull())
        throw VMError::UseNullValueError(defLine, defColumn);

    this->value = std::make_shared<sakValue>(std::move(val));
    return *this;
}

// FuncObject
FuncObject::FuncObject(std::string n, sakFnArgsList args, std::vector<INS::Instruction> bdy, sakType::sakTid retType, int ln, int col)
    : fnArgs(std::move(args)), fnBody(std::move(bdy)), fnReturnType(retType) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}

sakFnArgsList& FuncObject::getArgs() {
    return fnArgs;
}

std::vector<INS::Instruction>& FuncObject::getBody() {
    return fnBody;
}

const sakType::sakTid& FuncObject::getReturnType() {
    return fnReturnType;
}

// StructObject
StructObject::StructObject(std::string n, std::vector<ValueObject> mems, int ln, int col) {
    this->objName = std::move(n);
    for (auto& m : mems) {
        this->members.push_back(std::make_shared<ValueObject>(m));
    }
    this->defLine = ln;
    this->defColumn = col;
}

bool StructObject::hasMember(std::string n) {
    for (const auto& m : members) {
        if (m->getName() == n) return true;
    }
    return false;
}

ValueObject& StructObject::getMember(std::string n) {
    for (const auto& m : members) {
        if (m->getName() == n) return *m;
    }
    throw VMError::UnknownIdentifierError(n, defLine, defColumn);
}

// CustomTypeObject
CustomTypeObject::CustomTypeObject(std::string n, std::vector<std::shared_ptr<Object>> mems, int ln, int col) {
    this->objName = std::move(n);
    this->members = std::move(mems);
    this->defLine = ln;
    this->defColumn = col;
}

bool CustomTypeObject::hasMember(std::string n) {
    for (const auto& m : members) {
        if (m->getName() == n) return true;
    }
    return false;
}

Object& CustomTypeObject::getObject(std::string n) {
    for (const auto& m : members) {
        if (m->getName() == n) return *m;
    }
    throw VMError::UnknownIdentifierError(n, defLine, defColumn);
}

// Object
Object::Object(std::string n, ValueObject valObj, int ln, int col) : object(valObj) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}
Object::Object(std::string n, FuncObject fnObj, int ln, int col) : object(fnObj) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}
Object::Object(std::string n, StructObject stctObj, int ln, int col) : object(stctObj) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}
Object::Object(std::string n, CustomTypeObject cttObj, int ln, int col) : object(cttObj) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}
Object::Object(std::string n, sakValue value, sakType::sakTid tid, int ln, int col) : object(ValueObject(n, value, tid, ln, col)) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}
Object::Object(std::string n, sakType::sakTid tid, int ln, int col) : object(ValueObject(n, tid, ln, col)) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}
Object::Object(std::string n, sakValue value, int ln, int col) : object(ValueObject(n, value, ln, col)) {
    this->objName = std::move(n);
    this->defLine = ln;
    this->defColumn = col;
}

const int& Object::getLine() {
    return defLine;
}

const int& Object::getColumn() {
    return defColumn;
}

bool Object::isValueObj() {
    return std::holds_alternative<ValueObject>(object);
}
bool Object::isFnObj() {
    return std::holds_alternative<FuncObject>(object);
}
bool Object::isCustomTypeObj() {
    return std::holds_alternative<CustomTypeObject>(object);
}
bool Object::isStructObj() {
    return std::holds_alternative<StructObject>(object);
}

ValueObject& Object::getValueObj() {
    if (!isValueObj()) throw VMError::TypeInconsistentError("ValueObject", "other object", 0, 0);
    return std::get<ValueObject>(object);
}
FuncObject& Object::getFnObj() {
    if (!isFnObj()) throw VMError::TypeInconsistentError("FuncObject", "other object", 0, 0);
    return std::get<FuncObject>(object);
}
CustomTypeObject& Object::getCustomTypeObj() {
    if (!isCustomTypeObj()) throw VMError::TypeInconsistentError("CustomTypeObject", "other object", 0, 0);
    return std::get<CustomTypeObject>(object);
}
StructObject& Object::getStructObj() {
    if (!isStructObj()) throw VMError::TypeInconsistentError("StructObject", "other object", 0, 0);
    return std::get<StructObject>(object);
}
