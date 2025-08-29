#ifndef SAKORA_THREAD_H
#define SAKORA_THREAD_H

#include "../instruction.h"

namespace svm {
    using vmThread = std::vector<sakora::VMCode>;

    class threadGroup {
    public:
        std::vector<vmThread> threads;
        int t_index; // 代表现在所在thread的index
        int c_index; // 代表现在指向的VMCode的index

        threadGroup()=default;
        void createNewThread();  // 创建新的thread，并让t_index更新为现在的位置
        void removePrevThread(); // 将上一个使用的thread remove掉，并更新t_index为上一个位置
    };
}

#endif