#ifndef SAKORA_OBJECT_H
#define SAKORA_OBJECT_H

#include "instruction.h"
#include "type.h"
#include <iostream>
#include <map>

namespace sakora {
    struct FuncObject {
        std::string objName;
        std::map<std::string, TypeId> formalArgs;
        std::vector<VMCode> fnBody;
    };

    struct ClassObject {
        std::string objName;
        
    };
}

#endif