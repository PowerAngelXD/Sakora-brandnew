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

svm::vmThread svm::VMInstance::getCurrentThread() {
    return threadMgr.threads.at(threadMgr.t_index);
}

sakora::VMCode svm::VMInstance::getCurrentCode() {
    return getCurrentThread().at(threadMgr.c_index);
}

void svm::VMInstance::nextCode() {
    threadMgr.c_index ++;
    codeArgs = getCurrentThread().at(threadMgr.c_index).getArgs();
}

void svm::VMInstance::backCode() {
    threadMgr.c_index --;
    codeArgs = getCurrentThread().at(threadMgr.c_index).getArgs();
}

void svm::VMInstance::moveTo(int pos) {
    threadMgr.c_index = pos;
    codeArgs = getCurrentThread().at(threadMgr.c_index).getArgs();
}

void svm::VMInstance::moveOffset(int offset) {
    threadMgr.c_index = threadMgr.c_index + offset;
    codeArgs = getCurrentThread().at(threadMgr.c_index).getArgs();
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

void svm::VMInstance::vmAssign() {
    auto val = Pop();
    auto name = codeArgs.at(0);
    
    scopeMgr.
        currentScope->
        locate(name, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2)))->
        members[name] = val;
}

void svm::VMInstance::vmGet() {
    auto name = codeArgs.at(0);

    runtimeStack.push(scopeMgr.currentScope->locate(name, std::stoi(codeArgs.at(1)), std::stoi(codeArgs.at(2)))->members[name]);
}

void svm::VMInstance::vmFrom() {
    auto from_type = codeArgs.at(0);
    if (from_type == "[Index]") {
        auto index = Pop();
        auto arr = Pop();
        runtimeStack.push(arr.getStruct()->content.at(index.getInt()));
    }
}

void svm::VMInstance::vmNewScope() {
    scopeMgr.createScope();
}

void svm::VMInstance::vmEndScope() {
    scopeMgr.removeScope();
}

void svm::VMInstance::vmJmptin() {
    auto cond = Pop();
    if (cond.getBool()); // 为真，进入block
    else {
        // 为假，跳过block
        int st = 0;
        while (true) {
            nextCode();
            auto c = getCurrentCode();
            if (c.getOp() == sakora::NEW_SCOPE) st ++;
            else if (c.getOp() == sakora::END_SCOPE) st --;

            if (st == 0) break;
        }
    }
}

void svm::VMInstance::vmJmpbck() {
    auto cond = Pop();
    if (cond.getBool()) {
        // 为真，进入循环
        int st = 0;
        while (true) {
            backCode();
            auto c = getCurrentCode();
            if (c.getOp() == sakora::END_SCOPE) st ++;
            else if (c.getOp() == sakora::NEW_SCOPE) st --;

            if (st == 0) break;
        }
    }
    else {} // 为假，跳出循环
}
//

void svm::VMInstance::clearThenLoad(vmThread thread) {
    threadMgr.threads.clear();
    threadMgr.t_index = -1;
    threadMgr.createNewThread();
    threadMgr.threads.at(threadMgr.t_index) = thread;
}

void svm::VMInstance::load(vmThread thread) {
    threadMgr.createNewThread();
    threadMgr.threads.at(threadMgr.t_index) = thread;
}

void svm::VMInstance::start(bool isDebug) {
    for (; threadMgr.c_index < static_cast<int>(getCurrentThread().size()); threadMgr.c_index ++) {
        auto code = getCurrentCode();
        switch (code.getOp())
        {
        case sakora::PUSH:
            vmPush();
            break;
        case sakora::ADD:
            vmAdd();
            break;
        case sakora::SUB:
            vmSub();
            break;
        case sakora::MUL:
            vmMul();
            break;  
        case sakora::DIV:
            vmDiv();
            break;
        case sakora::LGC_AND:
            vmLgcAnd();
            break;
        case sakora::LGC_OR:
            LgcOr();
            break;
        case sakora::LGC_EQU:
            vmLgcEqu();
            break;
        case sakora::LGC_NOT:
            vmLgcNot();
            break;
        case sakora::LGC_MR_THAN:
            vmLgcMrThan();
            break;
        case sakora::LGC_LS_THAN:
            vmLgcLsThan();
            break;
        case sakora::LGC_MREQU_THAN:
            vmLgcMrequThan();
            break;
        case sakora::LGC_LSEQU_THAN:
            vmLgcLsequThan();
            break;
        case sakora::ARR_MAKE:
            vmArrMake();
            break;
        case sakora::ARR_TIDY_CHK:
            vmArrTidyChk();
            break;
        case sakora::DECLARE:
            vmDeclare();
            break;
        case sakora::ASSIGN:
            vmAssign();
            break;
        case sakora::GET:
            vmGet();
            break;
        case sakora::FROM:
            vmFrom();
            break;
        case sakora::NEW_SCOPE:
            vmNewScope();
            break;
        case sakora::END_SCOPE: 
            vmEndScope();
            break;
        case sakora::JTIN:
            vmJmptin();
            break;
        case sakora::JTBCK:
            vmJmpbck();
            break;
        case sakora::FLAG:
            break;
        
        default:
            break;
        }
    }

    if (isDebug) {
        if (!runtimeStack.empty()) {
            auto rt = runtimeStack.top();
            std::cout << "[Result]: " << rt.toString() << std::endl;
            std::cout << "[Type]: " << rt.inferType().toString() << std::endl;
        }
        else std::cout << "[No result]" << std::endl;
    }
}