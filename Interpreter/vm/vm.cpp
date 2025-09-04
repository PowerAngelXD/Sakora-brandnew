#include "vm.h"

inline sakora::Value svm::VMInstance::Pop() {
    auto val = runtimeStack.top();
    runtimeStack.pop();
    return val;
}

void svm::VMInstance::newThread() {
    threadMgr.createNewThread();
}

void svm::VMInstance::removeThread() {
    threadMgr.removePrevThread();
}

// VMCode
void svm::VMInstance::vmPush() {
    auto s_val = codeArgs.at(0); // push指令的第一个参数意为push进入一个值
    if (s_val == "true" || s_val == "false") {
        runtimeStack.push(sakora::cstr2Bool(s_val, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2))));
    }
    else if (s_val.find('.') != std::string::npos) {
        runtimeStack.push(sakora::cstr2Float(s_val, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2))));
    }
    else if (s_val.front() == '\"' && s_val.back() == '\"') {
        runtimeStack.push(sakora::cstr2Str(s_val, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2))));
    }
    else if (s_val.front() == '\'' && s_val.back() == '\'') {
        runtimeStack.push(sakora::cstr2Char(s_val, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2))));
    }
    else {
        runtimeStack.push(sakora::cstr2Int(s_val, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2))));
    }
}

void svm::VMInstance::vmAdd() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval + rval);
}

void svm::VMInstance::vmSub() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval - rval);
}

void svm::VMInstance::vmMul() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval * rval);
}

void svm::VMInstance::vmDiv() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval / rval);
}

void svm::VMInstance::vmLgcAnd() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval && rval);
}

void svm::VMInstance::LgcOr() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval || rval);
}

void svm::VMInstance::vmLgcEqu() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval == rval);
}

void svm::VMInstance::vmLgcNot() {
    auto val = Pop();
    runtimeStack.push(!val);
}

void svm::VMInstance::vmLgcMrThan() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval > rval);
}

void svm::VMInstance::vmLgcLsThan() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval < rval);
}

void svm::VMInstance::vmLgcMrequThan() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval >= rval);
}

void svm::VMInstance::vmLgcLsequThan() {
    auto rval = Pop();
    auto lval = Pop();
    runtimeStack.push(lval <= rval);
}

void svm::VMInstance::vmArrMake() {
    int arrSize = std::stoi(codeArgs.at(0)); // mkarr指令的第一个参数意为数组大小
    std::vector<sakora::Value> arr;
    for (int i = 0; i < arrSize; ++i) {
        arr.push_back(Pop());
    }
    std::reverse(arr.begin(), arr.end());
    runtimeStack.push(sakora::Value(sakora::StructValue{arr, sakora::Array}, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2))));
}

void svm::VMInstance::vmArrTidyChk() {
    auto arr = Pop();
    auto arr_t = arr.inferType();
    auto f_len = arr_t.getArrMod().lengthList.at(0);
    for (auto len : arr_t.getArrMod().lengthList) {
        if (len != f_len)
            throw VMError::NotTidyArrayError(std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2)));
    }
    runtimeStack.push(arr);
}

void svm::VMInstance::vmDeclare() {
    auto val = Pop();
    auto name = codeArgs.at(0); // declare指令的第一个参数意为变量名
    if (scopeMgr.currentScope->isExist(name)) {
        throw VMError::AlreadyIdentifierError(name, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2)));
    }
    scopeMgr.currentScope->members[name] = val;
}

//