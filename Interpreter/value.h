#ifndef SAKORA_VALUE_H
#define SAKORA_VALUE_H

#include "type.h"
#include "object.h"
#include <variant>
#include <sstream>

namespace sakora {
    class StructValue;
    using StructPtr = std::shared_ptr<StructValue>;
    enum StructKind { Array, Tuple };

    using ObjectPtr = std::shared_ptr<Object>;

    // 单值，不是结构
    class Value {
        std::variant<int, double, std::string, char, bool, std::nullptr_t, StructPtr, ObjectPtr> value;
        int line, column;
    public:
        Value(int val, int ln, int col);
        Value(double val, int ln, int col);
        Value(std::string val, int ln, int col);
        Value(char val, int ln, int col);
        Value(bool val, int ln, int col);
        Value(StructValue stct_val, int ln, int col);
        Value(int ln, int col); // 初始为Null

        int getInt();
        double getFloat();
        std::string getString();
        char getChar();
        bool getBool();
        StructPtr getStruct();

        void intAssign(int i);
        void floatAssign(double f);
        void stringAssign(std::string s);
        void charAssign(char c);
        void boolAssign(bool b);
        void nullAssign();

        std::vector<int> inferLengthList(std::vector<Value> arr, std::vector<int> initd = {});
        int inferDimension(std::vector<Value> arr, int initd = 1);
        TypeId inferFinalType(std::vector<Value> arr);
        TypeId inferType();

        std::string toString();
    };

    // 将结构包装成值
    struct StructValue {
        std::vector<Value> content;
        StructKind kind;
    };
}

#endif