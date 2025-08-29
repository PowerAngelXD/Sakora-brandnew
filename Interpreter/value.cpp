#include "value.h"

sakora::Value::Value(int val, int ln, int col)
    : value(val), line(ln), column(col) {}
sakora::Value::Value(double val, int ln, int col)
    : value(val), line(ln), column(col) {}
sakora::Value::Value(std::string val, int ln, int col)
    : value(val), line(ln), column(col) {}
sakora::Value::Value(char val, int ln, int col)
    : value(val), line(ln), column(col) {}
sakora::Value::Value(bool val, int ln, int col)
    : value(val), line(ln), column(col) {}
sakora::Value::Value(StructValue stct_val, int ln, int col) 
    : value(std::make_shared<StructValue>(stct_val)), line(ln), column(col) {}
sakora::Value::Value(int ln, int col)
    : value(nullptr), line(ln), column(col) {}

int sakora::Value::getInt() {
    if (std::holds_alternative<int>(value))
        return std::get<int>(value);
    throw std::runtime_error("Type error: Expected Int at line " + std::to_string(line) + ", column " + std::to_string(column));
}
double sakora::Value::getFloat() {
    if (std::holds_alternative<double>(value))
        return std::get<double>(value);
    throw std::runtime_error("Type error: Expected Float at line " + std::to_string(line) + ", column " + std::to_string(column));
}
std::string sakora::Value::getString() {
    if (std::holds_alternative<std::string>(value))
        return std::get<std::string>(value);
    throw std::runtime_error("Type error: Expected String at line " + std::to_string(line) + ", column " + std::to_string(column));
}
bool sakora::Value::getBool() {
    if (std::holds_alternative<bool>(value))
        return std::get<bool>(value);
    throw std::runtime_error("Type error: Expected Bool at line " + std::to_string(line) + ", column " + std::to_string(column));
}
char sakora::Value::getChar() {
    if (std::holds_alternative<char>(value))
        return std::get<char>(value);
    throw std::runtime_error("Type error: Expected Char at line " + std::to_string(line) + ", column " + std::to_string(column));
}
sakora::StructPtr sakora::Value::getStruct() {
    if (std::holds_alternative<StructPtr>(value))
        return std::get<StructPtr>(value);
    throw std::runtime_error("Type error: Expected Struct at line " + std::to_string(line) + ", column " + std::to_string(column));
}
void sakora::Value::intAssign(int i) {
    if (std::holds_alternative<int>(value))
        value = i;
    else
        throw std::runtime_error("Type error: Expected Int at line " + std::to_string(line) + ", column " + std::to_string(column));
}
void sakora::Value::floatAssign(double f) {
    if (std::holds_alternative<double>(value))
        value = f;
    else
        throw std::runtime_error("Type error: Expected Float at line " + std::to_string(line) + ", column " + std::to_string(column));
}
void sakora::Value::stringAssign(std::string s) {
    if (std::holds_alternative<std::string>(value))
        value = s;
    else
        throw std::runtime_error("Type error: Expected String at line " + std::to_string(line) + ", column " + std::to_string(column));
}
void sakora::Value::charAssign(char c) {
    if (std::holds_alternative<char>(value))
        value = c;
    else
        throw std::runtime_error("Type error: Expected Char at line " + std::to_string(line) + ", column " + std::to_string(column));
}
void sakora::Value::boolAssign(bool b) {
    if (std::holds_alternative<bool>(value))
        value = b;
    else
        throw std::runtime_error("Type error: Expected Bool at line " + std::to_string(line) + ", column " + std::to_string(column));
}
void sakora::Value::nullAssign() {
    if (std::holds_alternative<std::nullptr_t>(value))
        value = nullptr;
    else
        throw std::runtime_error("Type error: Expected Null at line " + std::to_string(line) + ", column " + std::to_string(column));
}

std::vector<int> sakora::Value::inferLengthList(std::vector<sakora::Value> arr, std::vector<int> initd) {
    std::vector<int> ret = initd;
    if (std::holds_alternative<sakora::StructPtr>(arr[0].value) && arr[0].getStruct()->kind == sakora::Array) {
        ret.push_back(static_cast<int>(arr.size()));
        return inferLengthList(arr[0].getStruct()->content, ret);
    }
    else {
        return initd;
    }
}
int sakora::Value::inferDimension(std::vector<sakora::Value> arr, int initd) {
    int ret = initd;

    auto element = arr[0];
    if (std::holds_alternative<StructPtr>(element.value) && element.getStruct()->kind == sakora::Array) {
        ret ++;
        return inferDimension(element.getStruct()->content, ret);
    }
    else {
        return ret;
    }
}
sakora::TypeId sakora::Value::inferFinalType(std::vector<sakora::Value> arr) {
    auto v = arr[0];
    if (std::holds_alternative<StructPtr>(v.value)) {
        return inferFinalType(v.getStruct()->content);
    }
    else {
        if (std::holds_alternative<int>(v.value))
            return TypeId(BasicType::Int);
        else if (std::holds_alternative<std::string>(v.value))
            return TypeId(BasicType::String);
        else if (std::holds_alternative<double>(v.value))
            return TypeId(BasicType::Float);
        else if (std::holds_alternative<bool>(v.value))
            return TypeId(BasicType::Bool);
        else if (std::holds_alternative<char>(v.value))
            return TypeId(BasicType::Char);
        else if (std::holds_alternative<std::nullptr_t>(v.value))
            return TypeId(BasicType::Null);
        else throw std::runtime_error("Unknown type at line " + std::to_string(v.line) + ", column " + std::to_string(v.column));
    }
}
sakora::TypeId sakora::Value::inferType() {
    if (!std::holds_alternative<StructPtr>(value)) {
        if (std::holds_alternative<int>(value))
            return TypeId(BasicType::Int);
        else if (std::holds_alternative<double>(value))
            return TypeId(BasicType::Float);
        else if (std::holds_alternative<std::string>(value))
            return TypeId(BasicType::String);
        else if (std::holds_alternative<char>(value))
            return TypeId(BasicType::Char);
        else if (std::holds_alternative<bool>(value))
            return TypeId(BasicType::Bool);
        else if (std::holds_alternative<std::nullptr_t>(value))
            return TypeId(BasicType::Null);
        else
            throw std::runtime_error("Unknown type at line " + std::to_string(line) + ", column " + std::to_string(column));
    }
    else {
        // 是结构类型
        // TODO: 支持其他结构之后，这里要做判断
        sakora::ArrayModifier arrMod;
        arrMod.dimension = inferDimension(getStruct()->content);
        arrMod.lengthList.push_back(static_cast<int>(getStruct()->content.size()));
        for (auto len : inferLengthList(getStruct()->content)) {
            arrMod.lengthList.push_back(len);
        }
        return TypeId(inferFinalType(getStruct()->content).getBasicType(), arrMod);
    }
}

std::string sakora::Value::toString() {
    std::ostringstream oss;
    if (std::holds_alternative<int>(value)) {
        oss << std::get<int>(value);
    }
    else if (std::holds_alternative<double>(value)) {
        oss << std::get<double>(value);
    }
    else if (std::holds_alternative<std::string>(value)) {
        oss << "\"" << std::get<std::string>(value) << "\"";
    }
    else if (std::holds_alternative<char>(value)) {
        oss << "'" << std::get<char>(value) << "'";
    }
    else if (std::holds_alternative<bool>(value)) {
        oss << (std::get<bool>(value) ? "true" : "false");
    }
    else if (std::holds_alternative<std::nullptr_t>(value)) {
        oss << "null";
    }
    else if (std::holds_alternative<StructPtr>(value)) {
        auto stct = std::get<StructPtr>(value);
        if (stct->kind == sakora::Array) {
            oss << "[";
            for (size_t i = 0; i < stct->content.size(); ++i) {
                oss << stct->content[i].toString();
                if (i != stct->content.size() - 1)
                    oss << ", ";
            }
            oss << "]";
        }
        else if (stct->kind == sakora::Tuple) {
            oss << "(";
            for (size_t i = 0; i < stct->content.size(); ++i) {
                oss << stct->content[i].toString();
                if (i != stct->content.size() - 1)
                    oss << ", ";
            }
            oss << ")";
        }
    }
    return oss.str();
}