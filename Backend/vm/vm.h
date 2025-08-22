#ifndef SAKORA_VM_H
#define SAKORA_VM_H

#include "../ins.h"
#include "../env/scope.h"
#include "vm_val.h"

#include <stack>
#include <algorithm>

// Sakora的解释器系统
class sakVM {
    std::vector<INS::Instruction> insSet;
    std::vector<VMVal> storage; // 临时储存容器
    std::stack<VMVal> runtime;  // 实际运行栈
    sakScope global; // 全局作用域

    std::size_t s_index;           // 管理临时储存的index

    void __sak_push(sakValue val);
    void __sak_push(Object& obj);
    sakValue __sak_pop();
    Object& __sak_pop_obj();
    void __sak_push_obj(sakValue name);
    void __sak_add();
    void __sak_sub();
    void __sak_div();
    void __sak_mul();
    void __sak_lgc_and();
    void __sak_lgc_or();
    void __sak_lgc_mr_than();
    void __sak_lgc_ls_than();
    void __sak_lgc_mrequ_than();
    void __sak_lgc_lsequ_than();
    void __sak_lgc_equ_than();
    void __sak_lgc_not_equ_than();
    void __sak_lgc_not();
    void __sak_make_array(sakValue val);
    void __sak_arr_tidy_check();
    void __sak_arr_tidy_check(std::vector<sakValue> arr);
    void __sak_declare(std::vector<sakValue> args);
    void __sak_assign();
    void __sak_get_val(sakValue name);
    void __sak_from(sakValue from_type);

public:
    sakVM();
    sakVM(std::vector<INS::Instruction> set);

    void run();
    sakValue& getTop();
    void loadCodes(std::vector<INS::Instruction> set);
};

#endif