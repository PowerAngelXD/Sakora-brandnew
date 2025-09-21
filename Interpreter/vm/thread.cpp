#pragma GCC optimize(3,"Ofast","inline")
#include "thread.h"

svm::threadGroup::threadGroup() {
    threads.emplace_back();
    t_index = 0;
    c_index = 0;
}

void svm::threadGroup::createNewThread() {
    vmThread newThread;

    threads.push_back(newThread);
    t_index ++;
    c_index = 0;
}

void svm::threadGroup::removePrevThread() {
    if (threads.size() <= 1) return; // 不能删完

    threads.erase(threads.begin() + t_index);
    t_index --;
    c_index = 0;
}