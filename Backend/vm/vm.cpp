#pragma GCC optimize(3,"Ofast","inline")
#include "vm.h"

sakVM::sakVM() : insSet({}), s_index(0), c_index(0) {}
sakVM::sakVM(std::vector<INS::Instruction> set)
     : insSet(set), s_index(0), c_index(0) {}

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
    Object obj = scopeMgr.getObject(name.getStrVal(), name.defLine, name.defColumn);
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
void sakVM::__sak_lgc_equ() {
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
            scopeMgr.createObject(obj);
        }
        else {
            // 仅声明
            auto obj = Object(objName, type.getTidVal(), type.defLine, type.defColumn);
            scopeMgr.createObject(obj);
        }
    }
    else {
        // 没有类型标注的情况
        auto value = __sak_pop();

        auto obj = Object(args.at(0).getStrVal(), value, value.defLine, value.defColumn);
        scopeMgr.createObject(obj);
    }
}
void sakVM::__sak_get_val(sakValue name) {
    auto obj = scopeMgr.getObject(name.getStrVal(), name.defLine, name.defColumn);
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

    scopeMgr.assignObject(obj);
}
void sakVM::__sak_jmp(sakValue jmp_type) {
    auto type = jmp_type.getStrVal();
    if (type == "[True-in]") {
        auto cond = __sak_pop();
        if (cond.getBoolVal());
            // 结果为True,进入下面的代码块
        else {
            // 结果为False跳过当前代码块
            int scopeState = 0;
            while (true) {
                c_index ++;
                if (insSet.at(c_index).getOp() == INS::NEW_SCOPE) scopeState ++;
                else if (insSet.at(c_index).getOp() == INS::END_SCOPE) scopeState --;

                if (scopeState == 0) break;
            }
        }
    }
    else if (type == "[Finish-out]") {
        if (runtime.empty()); // 未执行代码块，进行下一个条件判断（如果存在下一个条件判断的话）
        else {
            auto value = __sak_pop();
            while (true) {
                c_index ++;
                auto code = insSet.at(c_index);
                
                if (code.getOp() == INS::END_SCOPE && (code.getPara().getStrVal() == "[Tag=IfGroupEnd]" ||
                                                        code.getPara().getStrVal() == "[Tag=MatchGroupEnd]")) {
                    c_index --;
                    break;
                }
            }
        }
    }
    else if (type == "[Loop-back]") {
        if (runtime.empty());
        else {
            auto value = __sak_pop();
            while (true) {
                c_index --;
                if (!insSet.at(c_index).getParas().empty() && (insSet.at(c_index).getOp() == INS::NEW_SCOPE && insSet.at(c_index).getPara().getStrVal() == "[Tag=WhileGroupBegin]")) {
                    break;
                }
            }
        }
    }
}
void sakVM::__sak_new_scope(sakValue name) {
    scopeMgr.createScope(name.getStrVal());
}
void sakVM::__sak_end_scope() {
    scopeMgr.deleteCurrent();
}
//

void sakVM::loadCodes(std::vector<INS::Instruction> set) {
    this->insSet = set;
}

void sakVM::run() {
    c_index = 0; s_index = 0;
    storage.clear();
    for (;c_index < insSet.size(); c_index ++) {
        auto code = insSet.at(c_index);
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
            __sak_lgc_equ();
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
        case INS::JMP:
            __sak_jmp(code.getPara());
            break;
        case INS::NEW_SCOPE:
            __sak_new_scope(code.getPara());
            break;
        case INS::END_SCOPE:
            __sak_end_scope();
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
 
sakValue sakVM::getTop() {
    return runtime.top().getValue();
}