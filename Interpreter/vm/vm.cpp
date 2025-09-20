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
    if (codeArgs.at(1) == sakora::CodeArgs::Push::VAL) {
        if (s_val == "true" || s_val == "false") {
            runtimeStack.push(sakora::cstr2Bool(s_val, getCurrentCode().line, getCurrentCode().column));
        }
        else if (s_val.find('.') != std::string::npos) {
            runtimeStack.push(sakora::cstr2Float(s_val, getCurrentCode().line, getCurrentCode().column));
        }
        else if (s_val.front() == '\"' && s_val.back() == '\"') {
            runtimeStack.push(sakora::cstr2Str(s_val, getCurrentCode().line, getCurrentCode().column));
        }
        else if (s_val.front() == '\'' && s_val.back() == '\'') {
            runtimeStack.push(sakora::cstr2Char(s_val, getCurrentCode().line, getCurrentCode().column));
        }
        else {
            runtimeStack.push(sakora::cstr2Int(s_val, getCurrentCode().line, getCurrentCode().column));
        }
    }
    else if (codeArgs.at(1) == sakora::CodeArgs::Push::IDEN) {
        runtimeStack.push(sakora::Value({s_val}, getCurrentCode().line, getCurrentCode().column));
    }
    else if (codeArgs.at(1) == sakora::CodeArgs::Push::TYPE) {
        auto type_str = codeArgs.at(0);
        std::string basic_type; //0123456
        std::size_t i = 0; //    "int|123"
        for (; i < type_str.length(); i ++) {
            if (type_str.at(i) == '|') break;
            basic_type += type_str.at(i);
        }

        if (type_str.length() > i + 1) {
            // 后面还有内容，可能是array等类型
            i ++;
            std::string type_kind;
            for (; i < type_str.length(); i ++) {
                if (type_str.at(i) == '|') break;
                type_kind += type_str.at(i);
            }
            if (type_kind == "array") {
                sakora::ArrayModifier amod;
                i ++;
                for (; i < type_str.length(); i ++) {
                    std::string temp;

                    amod.dimension ++;
                    temp += type_str.at(i);
                    amod.lengthList.push_back(std::stoi(temp.c_str()));
                }

                if (basic_type == "int") 
                    runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Int, amod), getCurrentCode().line, getCurrentCode().column));
                else if (basic_type == "string") 
                    runtimeStack.push(sakora::Value(sakora::TypeId(sakora::String, amod), getCurrentCode().line, getCurrentCode().column));
                else if (basic_type == "char") 
                    runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Char, amod), getCurrentCode().line, getCurrentCode().column));
                else if (basic_type == "float") 
                    runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Float, amod), getCurrentCode().line, getCurrentCode().column));
                else if (basic_type == "bool") 
                    runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Bool, amod), getCurrentCode().line, getCurrentCode().column));
                else if (basic_type == "tid") 
                    runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Tid, amod), getCurrentCode().line, getCurrentCode().column));
            }
        }
        else {
            // 是普通类型
            if (basic_type == "int") 
                runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Int), getCurrentCode().line, getCurrentCode().column));
            else if (basic_type == "string") 
                runtimeStack.push(sakora::Value(sakora::TypeId(sakora::String), getCurrentCode().line, getCurrentCode().column));
            else if (basic_type == "char") 
                runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Char), getCurrentCode().line, getCurrentCode().column));
            else if (basic_type == "float") 
                runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Float), getCurrentCode().line, getCurrentCode().column));
            else if (basic_type == "bool") 
                runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Bool), getCurrentCode().line, getCurrentCode().column));
            else if (basic_type == "tid") 
                runtimeStack.push(sakora::Value(sakora::TypeId(sakora::Tid), getCurrentCode().line, getCurrentCode().column));
        }
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
    auto code = getCurrentCode();
    runtimeStack.push(sakora::Value(sakora::StructValue{arr, sakora::Array}, code.line, code.column));
}

void svm::VMInstance::vmArrTidyChk() {
    auto arr = Pop();
    auto arr_t = arr.inferType();
    auto f_len = arr_t.getArrMod().lengthList.at(0);
    auto code = getCurrentCode();
    for (auto len : arr_t.getArrMod().lengthList) {
        if (len != f_len)
            throw VMError::NotTidyArrayError(code.line, code.column);
    }
    runtimeStack.push(arr);
}

void svm::VMInstance::vmDeclare() {
    if (codeArgs.at(1) == sakora::CodeArgs::Declare::HAS_TMOD) {
        auto type = Pop();
        auto val = Pop();
        if (val.inferType() != type.getTypeIdValue()) 
            throw VMError::NotMatchedTypeError(type.getTypeIdValue().toString(), getCurrentCode().line, getCurrentCode().column);
        
        scopeMgr.declare(codeArgs.at(0), val);
    }
    else {
        auto val = Pop();
        scopeMgr.declare(codeArgs.at(0), val);
    }
}

void svm::VMInstance::vmAssign() {
    auto val = Pop();
    auto name = Pop().getIdenResult();
    
    auto code = getCurrentCode();
    scopeMgr.get(name.at(0), code.line, code.column) = val; // TODO: 未来加入结构体之后这里需要修改
}

void svm::VMInstance::vmGet() {
    auto name = codeArgs.at(0);
    auto code = getCurrentCode();
    runtimeStack.push(scopeMgr.get(name, code.line, code.column));
}

void svm::VMInstance::vmFrom() {
    auto from_type = codeArgs.at(0);
    if (from_type == "[Index]") {
        auto index = Pop();
        auto arr = Pop();
        runtimeStack.push(arr.getStruct()->content.at(index.getInt()));
    }
}

void svm::VMInstance::vmBlockStart() {
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
            if (c.getOp() == sakora::BLOCK_START) st ++;
            else if (c.getOp() == sakora::BLOCK_END) st --;

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
            if (c.getOp() == sakora::BLOCK_END) st ++;
            else if (c.getOp() == sakora::BLOCK_START) st --;

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
        codeArgs = code.getArgs();
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
        case sakora::BLOCK_START:
            vmBlockStart();
            break;
        case sakora::BLOCK_END: 
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