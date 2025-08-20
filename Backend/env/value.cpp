#include "value.h"
#include "type/sak_int.h"
#include "type/sak_string.h"
#include "type/sak_float.h"
#include "type/sak_bool.h"

sakValue::sakValue(int&& v, int ln, int col) : value(sakType::sakInt(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(std::string&& v, int ln, int col) : value(sakType::sakString(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(double&& v, int ln, int col) : value(sakType::sakFloat(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(bool&& v, int ln, int col) : value(sakType::sakBool(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(char&& v, int ln, int col) : value(sakType::sakChar(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::Type&& v, int ln, int col) : value(sakType::sakTid(v)), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakChar cv, int ln, int col) : value(cv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakTid tv, int ln, int col) : value(tv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakFloat fv, int ln, int col) : value(fv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakInt iv, int ln, int col) : value(iv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakString sv, int ln, int col) : value(sv), defLine(ln), defColumn(col) {}
sakValue::sakValue(sakType::sakBool bv, int ln, int col) : value(bv), defLine(ln), defColumn(col) {}

sakValue::sakValue(structPtr svs) : value(svs) {}

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
    else if (std::holds_alternative<sakType::sakTid>(value)) {
        return sakType::Type::Tid;
    }
    else if (std::holds_alternative<sakType::sakChar>(value)) {
        return sakType::Type::Char;
    }
    else return sakType::Type::EMPTY;
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

const char& sakValue::getCharVal() {
    if (!std::holds_alternative<sakType::sakChar>(value)) {
        throw std::runtime_error("sakValue: not a char");
    }
    return std::get<sakType::sakChar>(value).getVal();
}

const bool& sakValue::getBoolVal() {
    if (!std::holds_alternative<sakType::sakBool>(value)) {
        throw std::runtime_error("sakValue: not a bool");
    }
    return std::get<sakType::sakBool>(value).getVal();
}

sakType::sakTid sakValue::getTidVal() {
    return std::get<sakType::sakTid>(value);
}

bool sakValue::isStruct() {
    return !std::holds_alternative<sakType::sakInt>(value) &&
            !std::holds_alternative<sakType::sakFloat>(value) &&
            !std::holds_alternative<sakType::sakBool>(value) &&
            !std::holds_alternative<sakType::sakTid>(value) &&
            !std::holds_alternative<sakType::sakString>(value) &&
            !std::holds_alternative<sakType::sakChar>(value);
}

sakStruct& sakValue::getStruct() {
    return *std::get<structPtr>(value);
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
sakValue sakValue::createCharVal(std::string s, int ln, int col) {
    return sakValue(sakType::sakChar(s[0]), ln, col);

}
sakValue sakValue::operator +(sakValue val) {
    switch (this->getType())
    {
    case sakType::Type::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakInt(this->getIntVal() + val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Float) {
            return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) + val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("+", val.defLine, val.defColumn);
        }
    case sakType::Type::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() + val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Int) {
            return sakValue(sakType::sakFloat(static_cast<int>(this->getFloatVal()) + val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("+", val.defLine, val.defColumn);
        }
    case sakType::Type::String:
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
    case sakType::Type::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakInt(this->getIntVal() - val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Float) {
            return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) - val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("-", val.defLine, val.defColumn);
        }
    case sakType::Type::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() - val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Int) {
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
    case sakType::Type::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakInt(this->getIntVal() * val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Float) {
            return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) * val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::String) {
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
    case sakType::Type::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() * val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Int) {
            return sakValue(sakType::sakFloat(static_cast<int>(this->getFloatVal()) * val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("*", val.defLine, val.defColumn);
        }
    case sakType::Type::String:
        if (val.getType() == sakType::Type::Int) {
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
    case sakType::Type::Int: 
        if (val.getType() == this->getType()) {
            if ((static_cast<double>(this->getIntVal()) / val.getIntVal()) == std::trunc(static_cast<double>(this->getIntVal()) / val.getIntVal())) {
                return sakValue(sakType::sakInt(this->getIntVal() / val.getIntVal()), this->defLine, this->defColumn);
            }
            else {
                return sakValue(sakType::sakFloat(static_cast<double>(this->getIntVal()) / val.getIntVal()), this->defLine, this->defColumn);
            }
        }
        else if (val.getType() == sakType::Type::Float) {
            return sakValue(sakType::sakFloat((this->getIntVal()) / val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedOperatorError("/", val.defLine, val.defColumn);
        }
    case sakType::Type::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakFloat(this->getFloatVal() / val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Int) {
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
    case sakType::Type::Boolean:
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
    case sakType::Type::Boolean:
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
sakValue sakValue::operator >(sakValue val) {
    switch (this->getType())
    {
    case sakType::Type::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getIntVal() > val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Float) {
            return sakValue(sakType::sakBool(this->getIntVal() > val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'>'", val.defLine, val.defColumn);
        }
    case sakType::Type::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getFloatVal() > val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Int) {
            return sakValue(sakType::sakBool(this->getFloatVal() > val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'>'", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("'>'", val.defLine, val.defColumn);
    }
}
sakValue sakValue::operator >=(sakValue val) {
    return sakValue(sakType::sakBool(((this->operator>(val)).getBoolVal() && (this->operator==(val)).getBoolVal())), this->defLine, this->defColumn);
}
sakValue sakValue::operator <(sakValue val) {
    switch (this->getType())
    {
    case sakType::Type::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getIntVal() < val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Float) {
            return sakValue(sakType::sakBool(this->getIntVal() < val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'<'", val.defLine, val.defColumn);
        }
    case sakType::Type::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getFloatVal() < val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Int) {
            return sakValue(sakType::sakBool(this->getFloatVal() < val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'<'", val.defLine, val.defColumn);
        }
    default:
        throw VMError::NotMatchedTypeError("'<'", val.defLine, val.defColumn);
    }
}
sakValue sakValue::operator <=(sakValue val) {
    return sakValue(sakType::sakBool(((this->operator<(val)).getBoolVal() && (this->operator==(val)).getBoolVal())), this->defLine, this->defColumn);
}
sakValue sakValue::operator ==(sakValue val) {
    switch (this->getType())
    {
    case sakType::Type::String:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getStrVal() == val.getStrVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'=='", val.defLine, val.defColumn);
        }
    case sakType::Type::Boolean:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getBoolVal() == val.getBoolVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'=='", val.defLine, val.defColumn);
        }
    case sakType::Type::Int:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getIntVal() == val.getIntVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Float) {
            return sakValue(sakType::sakBool(this->getIntVal() == val.getFloatVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'=='", val.defLine, val.defColumn);
        }
    case sakType::Type::Float:
        if (val.getType() == this->getType()) {
            return sakValue(sakType::sakBool(this->getFloatVal() == val.getFloatVal()), this->defLine, this->defColumn);
        }
        else if (val.getType() == sakType::Type::Int) {
            return sakValue(sakType::sakBool(this->getFloatVal() == val.getIntVal()), this->defLine, this->defColumn);
        }
        else {
            throw VMError::NotMatchedTypeError("'=='", val.defLine, val.defColumn);
        }
    default: 
        if (this->getType() == sakType::Type::EMPTY) {
            if ((this->isStruct() && this->getStruct().isArray()) &&
                (val.isStruct() && val.getStruct().isArray())) {
                    return sakValue(sakType::sakBool(sakStruct::isArrEqual(this->getStruct().getArray(), val.getStruct().getArray())), this->defLine, this->defColumn);
                }
            else throw VMError::NotMatchedTypeError("'=='", val.defLine, val.defColumn);
        }
        else throw VMError::NotMatchedTypeError("'=='", val.defLine, val.defColumn);
    }
}
sakValue sakValue::operator !=(sakValue val) {
    return sakValue(sakType::sakBool(!(this->operator==(val)).getBoolVal()), this->defLine, this->defColumn);
}
sakValue sakValue::operator !() {
    if (this->getType() == sakType::Type::Boolean) {
        return sakValue(sakType::sakBool(!this->getBoolVal()), this->defLine, this->defColumn);
    }
    else {
        throw VMError::NotMatchedTypeError("'!'", this->defLine, this->defColumn);
    }
}

std::string sakValue::toString() {
    std::ostringstream oss;
    switch (getType()) {
        case sakType::Type::Int:
            oss << getIntVal();
            break;
        case sakType::Type::Float:
            oss << getFloatVal();
            break;
        case sakType::Type::String:
            oss << "\"" << getStrVal() << "\"";
            break;
        case sakType::Type::Boolean:
            oss << (getBoolVal() ? "true" : "false");
            break;
        case sakType::Type::Char:
            oss << '\'' << getCharVal() << '\'';
            break;
        case sakType::Type::Tid: {
            if (std::get<sakType::sakTid>(value).getVal() != sakType::Type::EMPTY) {
                std::string content;
                switch (this->getTidVal().getVal())
                {
                case sakType::Type::Boolean:
                    content = "<Boolean>";
                    break;
                case sakType::Type::String:
                    content = "<String>";
                    break;
                case sakType::Type::Int:
                    content = "<Int>";
                    break;
                case sakType::Type::Float:
                    content = "<Float>";
                    break;
                case sakType::Type::Tid:
                    content = "<TypeId>";
                    break;
                case sakType::Type::Char:
                    content = "<Char>";
                    break;
                default:
                    break;
                }
                oss << content;
            }
            else {
                if (std::get<sakType::sakTid>(value).getModifier().arrayMod) {
                    auto amr = std::get<sakType::sakTid>(value).getModifier().arrayMod;
                    switch (amr->arrayType)
                    {
                    case sakType::Type::Int:
                        oss << "<Int>";
                        break;
                    case sakType::Type::Float:
                        oss << "<Float>";
                        break;
                    case sakType::Type::String:
                        oss << "<String>";
                        break;
                    case sakType::Type::Boolean:
                        oss << "<Boolean>";
                        break;
                    case sakType::Type::Tid:
                        oss << "<Tid>";
                        break;
                    case sakType::Type::Char:
                        oss << "<Char>";
                        break;
                    default:
                        break;
                    }
                    for (auto info : amr->lengths) {
                        oss << "[" << info << "]";
                    }
                }
            }
            break;
        }
        default: {
            if (isStruct()) {
                    // 是struct，以struct的形式打印
                    auto s = getStruct();
                    if (s.isArray()) {
                        oss << "[";
                        for (std::size_t i = 0; i < s.getArray().size(); i ++) {
                            oss << s.getArray().at(i).toString();
                            if (i != s.getArray().size() - 1) {
                                oss << ", ";
                            }
                        }
                        oss << "]";
                    }
                }
        }
    }
    return oss.str();
}
void sakValue::printValue() {
    std::cout << this->toString();
}

void sakValue::printValueLn() {
    this->printValue();
    std::cout << std::endl;
}



// sakStruct

sakStruct::sakStruct(std::vector<sakValue> arrStruct) : type(StructType::Array), arrayStruct(arrStruct) {}

bool sakStruct::isArray() {
    return type == StructType::Array;
}

std::vector<sakValue> sakStruct::getArray() {
    return arrayStruct;
}
sakValue sakStruct::arrayAt(int index) {
    if (index > static_cast<int>(arrayStruct.size()) - 1)
        throw VMError::ArrayOutOfRangeError("ArrayOutOfRangeError", this->arrayStruct.at(0).defLine, this->arrayStruct.at(0).defColumn);
    else return arrayStruct.at(index);
}

bool sakStruct::isArrEqual(std::vector<sakValue> arr1, std::vector<sakValue> arr2) {
    if (arr1.size() != arr1.size()) return false;
    for (std::size_t i = 0; i < arr1.size(); i ++) {
        if ((arr1.at(i) != arr2.at(i)).getBoolVal()) return false;
    }
    return true;
}

// Public Function

sakValue sakValue::inferType() {
    if (!this->isStruct()) {
        return sakValue(sakType::sakTid(this->getType()), this->defLine, this->defColumn);
    }
    else {
        auto stct = this->getStruct();
        auto array = stct.getArray();
        sakType::ArrayModifider amdr;
        if (!array.at(0).isStruct()) {
            amdr.lengths.emplace_back(static_cast<int>(array.size()));
            amdr.dimension = 1;
            amdr.arrayType = array.at(0).getType();

            return sakValue(sakType::sakTid(sakType::Type::EMPTY, amdr), this->defLine, this->defColumn);
        }
        else {
            amdr.dimension = inferDimension(array);
            amdr.lengths.emplace_back(static_cast<int>(array.size()));
            for (auto e : inferLengths(array)) {
                amdr.lengths.emplace_back(e);
            }
            amdr.arrayType = inferFinalType(array);

            return sakValue(sakType::sakTid(sakType::Type::EMPTY, amdr), this->defLine, this->defColumn);
        }
    }
}

int sakValue::inferDimension(std::vector<sakValue> arr, int initd) {
    int d = initd;

    auto temp_a = arr.at(0);
    if (temp_a.isStruct()) {
        d ++;
        return inferDimension(temp_a.getStruct().getArray(), d);
    }
    else {
        return d;
    }
}

std::vector<int> sakValue::inferLengths(std::vector<sakValue> arr, std::vector<int> initd) {
    std::vector<int> d = initd;

    auto temp_a = arr.at(0);
    if (temp_a.isStruct()) {
        d.emplace_back(static_cast<int>(temp_a.getStruct().getArray().size()));
        return inferLengths(temp_a.getStruct().getArray(), d);
    }
    else {
        return d;
    }
}

sakType::Type sakValue::inferFinalType(std::vector<sakValue> arr) {
    auto temp_a = arr.at(0);
    if (temp_a.isStruct()) {
        return inferFinalType(temp_a.getStruct().getArray());
    }
    else {
        return temp_a.getType();
    }
}