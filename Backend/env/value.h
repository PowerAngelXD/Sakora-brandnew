#ifndef SAKORA_VALUE_H
#define SAKORA_VALUE_H

#include "type/type.h"
#include <memory>
#include <variant>



class sakValue {
    std::variant<sakType::sakInt, sakType::sakString, sakType::sakFloat> val;
public:
    sakValue(int&& v);
    sakValue(std::string&& v);
    sakValue(double&& v);
    sakValue(sakType::sakInt iv);
    sakValue(sakType::sakFloat fv);
    sakValue(sakType::sakString sv);

    sakType::Type getType();
    const int& getIntVal();
    const std::string& getStrVal();
    const double& getFloatVal();

    static sakValue genIntVal(std::string s);
    static sakValue genFloatVal(std::string s);
    static sakValue genStringVal(std::string s);
};

#endif