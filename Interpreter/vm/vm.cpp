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
    
}
//