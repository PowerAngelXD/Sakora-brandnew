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
        default:
            break;
        }
    }
    // for debug:
    std::cout << "[result]: " << runtime.top().getIntVal() << std::endl;
}
 
sakValue& sakVM::getTop() {
    return runtime.top();
}