#ifndef SAKORA_VM_H
#define SAKORA_VM_H

#include "thread.h"
#include "../scope.h"
#include <stack>

namespace svm {
    class VMInstance {
        std::stack<sakora::Value> runtimeStack;
        threadGroup threadMgr;
        sakora::ScopeManager scopeMgr;
        std::vector<std::string> codeArgs; // 当前code的args
    public:
        VMInstance()=default;

        // vm内工具方法
        inline sakora::Value Pop();
        void newThread();
        void removeThread();
        vmThread getCurrentThread();
        sakora::VMCode getCurrentCode();

        void nextCode();
        void backCode();
        void moveTo(int pos);
        void moveOffset(int offset = 0);
        // 对应的指令实现方法
        void vmPush();
        void vmAdd();       void vmSub();       void vmMul();          void vmDiv();
        void vmLgcAnd();    void LgcOr();       void vmLgcEqu();       void vmLgcNot();
        void vmLgcMrThan(); void vmLgcLsThan(); void vmLgcMrequThan(); void vmLgcLsequThan();
        void vmArrMake();   void vmArrTidyChk();
        void vmDeclare();   void vmAssign();    void vmGet();          void vmFrom();
        void vmBlockStart();  void vmEndScope();
        void vmJmptin();      void vmJmpbck();
        //

        void clearThenLoad(vmThread thread);
        void load(vmThread thread);
        void start(bool isDebug = false);

    };
}

#endif