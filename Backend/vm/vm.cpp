#include "vm.h"

sakVM::sakVM(std::vector<INS::Instruction> set) : insSet(set), s_index(0) {}

// code
void sakVM::__sak_push(sakValue val) {
    runtime.push(val);
}
sakValue sakVM::__sak_pop() {
    storage.emplace_back(runtime.top());
    runtime.pop();
    return storage.at(s_index ++);
}
void sakVM::__sak_add() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();

    __sak_push(lval + rval);
}
void sakVM::__sak_sub() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();

    __sak_push(lval - rval);
}
void sakVM::__sak_div() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();

    __sak_push(lval / rval);
}
void sakVM::__sak_mul() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();

    __sak_push(lval * rval);
}
void sakVM::__sak_lgc_and() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();

    __sak_push(lval && rval);
}
void sakVM::__sak_lgc_or() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();

    __sak_push(lval || rval);
}
void sakVM::__sak_lgc_mr_than() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();
    __sak_push(lval > rval);
}
void sakVM::__sak_lgc_ls_than() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();
    __sak_push(lval < rval);
}
void sakVM::__sak_lgc_mrequ_than() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();
    __sak_push(lval >= rval);
}
void sakVM::__sak_lgc_lsequ_than() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();
    __sak_push(lval <= rval);
}
void sakVM::__sak_lgc_equ_than() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();
    __sak_push(lval == rval);
}
void sakVM::__sak_lgc_not_equ_than() {
    auto rval = __sak_pop();
    auto lval = __sak_pop();
    __sak_push(lval != rval);
}
void sakVM::__sak_lgc_not() {
    auto val = __sak_pop();
    __sak_push(!val);
}
void sakVM::__sak_make_array(sakValue val) {
    auto length = val.getIntVal();

    std::vector<sakValue> array;
    for (int i = 0; i < length; i ++) {
        array.emplace_back(__sak_pop());
    }
    std::reverse(array.begin(), array.end());

    sakStruct arrayStruct = { array };
    __sak_push(sakValue(std::make_shared<sakStruct>(arrayStruct)));
}
void sakVM::__sak_arr_tidy_check() {
    auto arr = __sak_pop();
    __sak_arr_tidy_check(arr.getStruct().arrayStruct);

    __sak_push(arr);
}
void sakVM::__sak_arr_tidy_check(std::vector<sakValue> arr) {
    if (arr.at(0).isStruct()) {
        auto i_size = arr.at(0).getStruct().arrayStruct.size();
        for (auto sub_arr : arr) {
            if (sub_arr.getStruct().arrayStruct.size() != i_size) 
                throw VMError::NotTidyArrayError("NotTidyArrayError", arr.at(0).defLine, arr.at(0).defColumn);
            else if (!sub_arr.isStruct())
                throw VMError::NotTidyArrayError("NotTidyArrayError", arr.at(0).defLine, arr.at(0).defColumn);
            
            __sak_arr_tidy_check(sub_arr.getStruct().arrayStruct);
        }
    }
    else {
        for (std::size_t i = 1; i < arr.size(); i ++) {
            if (arr.at(i).isStruct())
                throw VMError::NotTidyArrayError("NotTidyArrayError", arr.at(0).defLine, arr.at(0).defColumn);
        }
    }
}
//

void sakVM::run() {
    for (auto code: insSet) {
        switch (code.getOp())
        {
        case INS::PUSH:
            __sak_push(code.getParas());
            break;
        case INS::POP:
            __sak_pop();
            break;
        case INS::ADD:
            __sak_add();
            break;
        case INS::SUB:
            __sak_sub();
            break;
        case INS::MUL:
            __sak_mul();
            break;
        case INS::DIV:
            __sak_div();
            break;
        case INS::LGC_AND:
            __sak_lgc_and();
            break;
        case INS::LGC_OR:
            __sak_lgc_or();
            break;
        case INS::LGC_MR_THAN:
            __sak_lgc_mr_than();
            break;
        case INS::LGC_LS_THAN:
            __sak_lgc_ls_than();
            break;
        case INS::LGC_MREQU_THAN:
            __sak_lgc_mrequ_than();
            break;
        case INS::LGC_LSEQU_THAN:
            __sak_lgc_lsequ_than();
            break;
        case INS::LGC_EQU:
            __sak_lgc_equ_than();
            break;
        case INS::LGC_NOT_EQU:
            __sak_lgc_not_equ_than();
            break;
        case INS::LGC_NOT:
            __sak_lgc_not();
            break;
        case INS::ARR_MAKE:
            __sak_make_array(code.getParas());
            break;
        case INS::ARR_TIDY_CHK:
            __sak_arr_tidy_check();
            break;
        default:
            break;
        }
    }
    // for debug:
    std::cout << "[result]: ";
    auto result = getTop();
    result.printValueLn();
    auto type = result.inferType();
    type.printValueLn();
}
 
sakValue& sakVM::getTop() {
    return runtime.top();
}