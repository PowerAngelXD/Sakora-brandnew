#ifndef SAKORA_VALUE_H
#define SAKORA_VALUE_H

#include "type/type.h"
#include "../../Error/VMError.h"
#include <memory>
#include <variant>


/// @brief sakora的解释器内值类，存放sakora基本数据类型对应的值并提供运算操作
class sakValue {
    std::variant<sakType::sakInt, 
                sakType::sakString, 
                sakType::sakFloat> value;

    int defLine;
    int defColumn;
public:
    // 构造函数
    sakValue(int&& v);
    sakValue(std::string&& v);
    sakValue(double&& v);
    sakValue(sakType::sakInt iv);
    sakValue(sakType::sakFloat fv);
    sakValue(sakType::sakString sv);
    sakValue(int&& v, int ln, int col);
    sakValue(std::string&& v, int ln, int col);
    sakValue(double&& v, int ln, int col);
    sakValue(sakType::sakInt iv, int ln, int col);
    sakValue(sakType::sakFloat fv, int ln, int col);
    sakValue(sakType::sakString sv, int ln, int col);

    // 功能函数
    void setDefPosition();
    sakType::Type getType();
    const int& getIntVal();
    const std::string& getStrVal();
    const double& getFloatVal();
    void printValue();

    // 运算符
    sakValue operator +(sakValue val);
    sakValue operator -(sakValue val);
    sakValue operator *(sakValue val);
    sakValue operator /(sakValue val);

    // 专门给generator使用的静态方法
    static sakValue genIntVal(std::string s, int ln, int col);
    static sakValue genFloatVal(std::string s, int ln, int col);
    static sakValue genStringVal(std::string s, int ln, int col);
};

#endif