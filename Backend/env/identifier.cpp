#include "identifier.h"

sakId::sakId(std::string i, sakValue val) {
    this->value = std::make_shared<sakValue>(std::move(val));
    this->id = i;
    this->idType = this->value->inferType().getTidVal();
}
sakId::sakId(std::string i, sakType::sakTid tid) {
    this->id = i;
    this->idType = tid;
}
sakId::sakId(std::string i, sakType::sakTid tid, sakValue val) {
    this->value = std::make_shared<sakValue>(val);
    this->id = i;
    this->idType = tid;

    auto type = sakValue(tid, val.defLine, val.defColumn);
    if (value->inferType().getTidVal() != idType) 
        throw VMError::TypeInconsistentError(type.toString(), val.toString(), val.defLine, val.defColumn);
}

const std::string& sakId::getId() {
    return id;
}

const sakValue& sakId::getVal() {
    return *value;
}

sakId& sakId::writeVal(sakValue val) {
    this->value.reset();
    this->value = std::make_shared<sakValue>(val);
    return *this;
}