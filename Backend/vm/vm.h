#ifndef SAKORA_VM_H
#define SAKORA_VM_H

#include "../ins.h"
#include "../env/value.h"

#include <stack>

// Sakora的解释器系统
class sakVM {
    std::vector<INS::Instruction> insSet;
    std::vector<sakValue> storage; // 临时储存容器
    std::stack<sakValue> runtime;  // 实际运行栈

    std::size_t s_index;           // 管理临时储存的index

    void __sak_push(sakValue val);
    sakValue __sak_pop();
    void __sak_add();
    void __sak_sub();
    void __sak_div();
    void __sak_mul();

public:
    sakVM(std::vector<INS::Instruction> set);

    void run();
    sakValue& getTop();
};

#endif