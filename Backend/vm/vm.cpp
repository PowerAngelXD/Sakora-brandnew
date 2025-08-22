#include "vm.h"

sakVM::sakVM() : insSet({}), global("__global__", {}), s_index(0) {}
sakVM::sakVM(std::vector<INS::Instruction> set) : insSet(set), global("__global__", {}), s_index(0) {}

// code
void sakVM::__sak_push(sakValue val) {
    runtime.push(val);
}
void sakVM::__sak_push(Object& obj) {
    runtime.push(obj);
}
sakValue sakVM::__sak_pop() {
    storage.emplace_back(runtime.top());
    runtime.pop();
    return storage.at(s_index ++).getValue();
}
Object& sakVM::__sak_pop_obj() {
    storage.emplace_back(runtime.top());
    runtime.pop();
    return storage.at(s_index ++).getObj();
}
void sakVM::__sak_push_obj(sakValue name) {
    Object& obj = global.getObj(name.getStrVal(), name.defLine, name.defColumn);
    __sak_push(obj);
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
    __sak_arr_tidy_check(arr.getStruct().getArray());

    __sak_push(arr);
}
void sakVM::__sak_arr_tidy_check(std::vector<sakValue> arr) {
    if (arr.at(0).isStruct()) {
        auto i_size = arr.at(0).getStruct().getArray().size();
        for (auto sub_arr : arr) {
            if (sub_arr.getStruct().getArray().size() != i_size) 
                throw VMError::NotTidyArrayError(arr.at(0).defLine, arr.at(0).defColumn);
            else if (!sub_arr.isStruct())
                throw VMError::NotTidyArrayError(arr.at(0).defLine, arr.at(0).defColumn);
            
            __sak_arr_tidy_check(sub_arr.getStruct().getArray());
        }
    }
    else {
        for (std::size_t i = 1; i < arr.size(); i ++) {
            if (arr.at(i).isStruct())
                throw VMError::NotTidyArrayError(arr.at(0).defLine, arr.at(0).defColumn);
        }
    }
}
void sakVM::__sak_declare(std::vector<sakValue> args) {
    if (args.size() == 2) {
        auto type = __sak_pop();
        auto objName = args.at(0).getStrVal();
        if (!runtime.empty()) {
            auto value = __sak_pop();

            auto obj = Object(objName, value, value.defLine, value.defColumn);
            global.addObj(obj); // TODO：后期等到多scope的时候这里应该是在currentScope中添加id
        }
        else {
            // 仅声明
            auto obj = Object(objName, type,  type.defLine, type.defColumn);
            global.addObj(obj); // TODO：后期等到多scope的时候这里应该是在currentScope中添加id
        }
    }
    else {
        // 没有类型标注的情况
        auto value = __sak_pop();

        auto obj = Object(args.at(0).getStrVal(), value, value.defLine, value.defColumn);
        global.addObj(obj); // TODO：后期等到多scope的时候这里应该是在currentScope中添加id
    }
}
void sakVM::__sak_get_val(sakValue name) {
    auto obj = global.getObj(name.getStrVal(), name.defLine, name.defColumn);
    if (obj.isValueObj() && !obj.getValueObj().isNull()) {
        auto val = obj.getValueObj().getValue();
        __sak_push(val);
    }
}
void sakVM::__sak_from(sakValue from_type) {
    if (from_type.getStrVal() == "[Index]") {
        auto index = __sak_pop();
        auto array = __sak_pop();
        __sak_push(array.getStruct().arrayAt(index.getIntVal()));
    }
}
void sakVM::__sak_assign() {
    auto obj = __sak_pop_obj();
    auto value = __sak_pop();
    obj.getValueObj().assign(value);

    global.update(obj);
}
//

void sakVM::loadCodes(std::vector<INS::Instruction> set) {
    this->insSet = set;
}

void sakVM::run() {
    for (auto code: insSet) {
        switch (code.getOp())
        {
        case INS::PUSH:
            __sak_push(code.getPara());
            break;
        case INS::POP:
            __sak_pop();
            break;
        case INS::PUSH_OBJ:
            __sak_push_obj(code.getPara());
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
            __sak_make_array(code.getPara());
            break;
        case INS::ARR_TIDY_CHK:
            __sak_arr_tidy_check();
            break;
        case INS::DECLARE:
            __sak_declare(code.getParas());
            break;
        case INS::ASSIGN:
            __sak_assign();
            break;
        case INS::GET_VAL:
            __sak_get_val(code.getPara());
            break;
        case INS::FROM:
            __sak_from(code.getPara());
            break;
        default:
            break;
        }
    }
    // for debug:
    std::cout << "[result]: ";
    if (runtime.empty()) {
        std::cout << "no result" << std::endl;
    }
    else {
        auto result = getTop();
        result.printValueLn();
        auto type = result.inferType();
        type.printValueLn();
    }
}
 
sakValue& sakVM::getTop() {
    return runtime.top().getValue();
}