#ifndef SAKORA_VALUE_H
#define SAKORA_VALUE_H

#include "type/type.h"
#include "../../Error/VMError.h"
#include <memory>
#include <variant>
#include <cmath>


/// @brief sakora的解释器内值类，存放sakora基本数据类型对应的值并提供运算操作
class sakValue {
    std::variant<sakType::sakInt, sakType::sakString, sakType::sakFloat, sakType::sakBool> value;

    int defLine;
    int defColumn;
public:
    // 构造函数
    sakValue(int&& v, int ln, int col);
    sakValue(std::string&& v, int ln, int col);
    sakValue(double&& v, int ln, int col);
    sakValue(bool&& v, int ln, int col);
    sakValue(sakType::sakInt iv, int ln, int col);
    sakValue(sakType::sakFloat fv, int ln, int col);
    sakValue(sakType::sakString sv, int ln, int col);
    sakValue(sakType::sakBool bv, int ln, int col);

    // 功能函数
    sakType::Type getType();
    const int& getIntVal();
    const std::string& getStrVal();
    const double& getFloatVal();
    const bool& getBoolVal();
    void printValue();

    // 运算符
    sakValue operator +(sakValue val);
    sakValue operator -(sakValue val);
    sakValue operator *(sakValue val);
    sakValue operator /(sakValue val);
    sakValue operator &&(sakValue val);
    sakValue operator ||(sakValue val);
    sakValue operator >(sakValue val);
    sakValue operator >=(sakValue val);
    sakValue operator <(sakValue val);
    sakValue operator <=(sakValue val);
    sakValue operator ==(sakValue val);
    sakValue operator !=(sakValue val);


    // 专门给generator使用的静态方法
    static sakValue createIntVal(std::string s, int ln, int col);
    static sakValue createFloatVal(std::string s, int ln, int col);
    static sakValue createStringVal(std::string s, int ln, int col);
    static sakValue createBoolVal(std::string s, int ln, int col);
};

#endif