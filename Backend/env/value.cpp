#include "value.h"
#include "type/sak_int.h"
#include "type/sak_string.h"
#include "type/sak_float.h"
#include <stdexcept>

sakValue::sakValue(int&& v) : val(sakType::sakInt(v)) {}
sakValue::sakValue(std::string&& v) : val(sakType::sakString(v)) {}
sakValue::sakValue(double&& v) : val(sakType::sakFloat(v)) {}
sakValue::sakValue(sakType::sakFloat fv) : val(fv) {}
sakValue::sakValue(sakType::sakInt iv) : val(iv) {}
sakValue::sakValue(sakType::sakString sv) : val(sv) {}

sakType::Type sakValue::getType() {
    if (std::holds_alternative<sakType::sakInt>(val)) {
        return sakType::Type::Int;
    } 
    else if (std::holds_alternative<sakType::sakString>(val)) {
        return sakType::Type::String;
    } 
    else if (std::holds_alternative<sakType::sakFloat>(val)) {
        return sakType::Type::Float;
    }
    throw std::runtime_error("sakValue: unknown type");
}

const int& sakValue::getIntVal() {
    if (!std::holds_alternative<sakType::sakInt>(val)) {
        throw std::runtime_error("sakValue: not an int");
    }
    return std::get<sakType::sakInt>(val).getVal();
}

const std::string& sakValue::getStrVal() {
    if (!std::holds_alternative<sakType::sakString>(val)) {
        throw std::runtime_error("sakValue: not a string");
    }
    return std::get<sakType::sakString>(val).getVal();
}

const double& sakValue::getFloatVal() {
    if (!std::holds_alternative<sakType::sakFloat>(val)) {
        throw std::runtime_error("sakValue: not a float");
    }
    return std::get<sakType::sakFloat>(val).getVal();
}


sakValue sakValue::genIntVal(std::string s) {
    return sakValue(sakType::sakInt(atoi(s.c_str())));
}
sakValue sakValue::genFloatVal(std::string s) {
    return sakValue(sakType::sakFloat(atof(s.c_str())));
}
sakValue sakValue::genStringVal(std::string s) {
    return sakValue(sakType::sakString(std::move(s)));
}
