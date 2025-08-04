#include "value.h"
#include "type/sak_int.h"
#include "type/sak_string.h"
#include "type/sak_float.h"
#include "type/sak_bool.h"
#include <stdexcept>
#include <iostream>

sakValue::sakValue(int&& v, int ln, int col) : value(sakType::sakInt(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(std::string&& v, int ln, int col) : value(sakType::sakString(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(double&& v, int ln, int col) : value(sakType::sakFloat(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(bool&& v, int ln, int col) : value(sakType::sakBool(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakFloat fv, int ln, int col) : value(fv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakInt iv, int ln, int col) : value(iv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakString sv, int ln, int col) : value(sv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakBool bv, int ln, int col) : value(bv), defLine(ln), defColumn(col) {}

sakType::Type sakValue::getType() {
    if (std::holds_alternative<sakType::sakInt>(value)) {
        return sakType::Type::Int;
    } 
    else if (std::holds_alternative<sakType::sakString>(value)) {
        return sakType::Type::String;
    } 
    else if (std::holds_alternative<sakType::sakFloat>(value)) {
        return sakType::Type::Float;
    }
    else if (std::holds_alternative<sakType::sakBool>(value)) {
        return sakType::Type::Boolean;
    }
    throw std::runtime_error("sakValue: unknown type");
}

const int& sakValue::getIntVal() {
    if (!std::holds_alternative<sakType::sakInt>(value)) {
        throw std::runtime_error("sakValue: not an int");
    }
    return std::get<sakType::sakInt>(value).getVal();
}

const std::string& sakValue::getStrVal() {
    if (!std::holds_alternative<sakType::sakString>(value)) {
        throw std::runtime_error("sakValue: not a string");
    }
    return std::get<sakType::sakString>(value).getVal();
}

const double& sakValue::getFloatVal() {
    if (!std::holds_alternative<sakType::sakFloat>(value)) {
        throw std::runtime_error("sakValue: not a float");
    }
    return std::get<sakType::sakFloat>(value).getVal();
}

const bool& sakValue::getBoolVal() {
    if (!std::holds_alternative<sakType::sakBool>(value)) {
        throw std::runtime_error("sakValue: not a bool");
    }
    return std::get<sakType::sakBool>(value).getVal();
}


sakValue sakValue::createIntVal(std::string s, int ln, int col) {
    return sakValue(sakType::sakInt(atoi(s.c_str())), ln, col);
}
sakValue sakValue::createFloatVal(std::string s, int ln, int col) {
    return sakValue(sakType::sakFloat(atof(s.c_str())), ln, col);
}
sakValue sakValue::createStringVal(std::string s, int ln, int col) {
    return sakValue(sakType::sakString(std::move(s)), ln, col);
}
sakValue sakValue::createBoolVal(std::string s, int ln, int col) {
    return sakValue(sakType::sakBool(s == "true"), ln, col);
}

sakValue sakValue::operator +(sakValue val) {
    switch (this->getType())
    {
    case sakType::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakInt(this->getIntVal() + val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Float) {
            return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) + val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("+", val.defLine, val.defColumn);
        }
    case sakType::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() + val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Int) {
            return sakValue(sakType::sakFloat(static_cast<int>(this->getFloatVal()) + val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("+", val.defLine, val.defColumn);
        }
    case sakType::String:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakString(this->getStrVal() + val.getStrVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("+", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("+", val.defLine, val.defColumn);
    }
}

sakValue sakValue::operator -(sakValue val) {
    switch (this->getType())
    {
    case sakType::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakInt(this->getIntVal() - val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Float) {
            return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) - val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("-", val.defLine, val.defColumn);
        }
    case sakType::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() - val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Int) {
            return sakValue(sakType::sakFloat(static_cast<int>(this->getFloatVal()) - val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("-", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("-", val.defLine, val.defColumn);
    }
}

sakValue sakValue::operator *(sakValue val) {
    switch (this->getType())
    {
    case sakType::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakInt(this->getIntVal() * val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Float) {
            return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) * val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::String) {
            auto times = this->getIntVal();
            auto result = val.getStrVal();
            auto bit = val.getStrVal();
            
            for (int i = 0; i < times - 1; i ++) {
                result += bit;
            }

            return sakValue(sakType::sakString(result), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("*", val.defLine, val.defColumn);
        }
    case sakType::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() * val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Int) {
            return sakValue(sakType::sakFloat(static_cast<int>(this->getFloatVal()) * val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("*", val.defLine, val.defColumn);
        }
    case sakType::String:
        if (val.getType() == sakType::Int) {
            auto times = val.getIntVal();
            auto result = this->getStrVal();
            auto bit = this->getStrVal();
            
            for (int i = 0; i < times - 1; i ++) {
                result += bit;
            }

            return sakValue(sakType::sakString(result), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("*", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("*", val.defLine, val.defColumn);
    }
}

sakValue sakValue::operator /(sakValue val) {
    switch (this->getType())
    {
    case sakType::Int: 
        if (val.getType() == this->getType()) {
            if ((static_cast<double>(this->getIntVal()) / val.getIntVal()) == std::trunc(static_cast<double>(this->getIntVal()) / val.getIntVal())) {
                return sakValue(sakType::sakInt(this->getIntVal() / val.getIntVal()), this->defLine, this->defColumn);
            }
            else {
                return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) / val.getIntVal()), this->defLine, this->defColumn);
            }
        }
        else if (val.getType() == sakType::Float) {
            return sakValue(sakType::sakFloat((this->getIntVal()) / val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("/", val.defLine, val.defColumn);
        }
    case sakType::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() / val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Int) {
            return sakValue(sakType::sakFloat(this->getFloatVal() / val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("/", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("/", val.defLine, val.defColumn);
    }
}

sakValue sakValue::operator &&(sakValue val) {
    switch (this->getType())
    {
    case sakType::Boolean:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getBoolVal() && val.getBoolVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("and", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("and", val.defLine, val.defColumn);
    }
}
sakValue sakValue::operator ||(sakValue val) {
    switch (this->getType())
    {
    case sakType::Boolean:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getBoolVal() || val.getBoolVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("or", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("or", val.defLine, val.defColumn);
    }
}

void sakValue::printValue() {
    switch (getType()) {
    case sakType::Int:
        std::cout << getIntVal() << std::endl;
        break;
    case sakType::Float:
        std::cout << getFloatVal() << std::endl;
        break;
    case sakType::String:
        std::cout << getStrVal() << std::endl;
        break;
    case sakType::Boolean:
        std::cout << (getBoolVal() ? "true" : "false") << std::endl;
        break;
    default:
        std::cout << "<Unknown Value>" << std::endl;
        break;
    }
}

