#ifndef SAKORA_OBJECT_H
#define SAKORA_OBJECT_H

#include "instruction.h"
#include "type.h"
#include <iostream>
#include <map>
#include <variant>

namespace sakora {
    struct FuncObject {
        int defLine, defColumn;

        std::string objName;
        std::map<std::string, TypeId> formalArgs;
        TypeId retType;
        std::vector<VMCode> fnBody;
    };

    struct StructObject {
        int defLine, defColumn;

        std::string objName;
        std::map<std::string, TypeId> fieldMembers;

        std::map<std::string, FuncObject> magicFnMembers;
    };

    struct ImplObject {
        int defLine, defColumn;

        std::string objName;
        std::shared_ptr<StructObject> implStruct = nullptr;
        std::map<std::string, FuncObject> fnMembers;

        std::map<std::string, FuncObject> magicFnMembers;
    };

    class Object {
        std::variant<FuncObject, StructObject, ImplObject> objContent;
    public:
        
    };
}

#endif