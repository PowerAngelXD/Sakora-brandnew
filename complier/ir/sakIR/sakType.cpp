#include "sakType.h"

bool sakIR::StructSet::hasMod() { return arrMod || tupleMod; }
bool sakIR::StructSet::isArr() { return arrMod != nullptr; }
bool sakIR::StructSet::isTuple() { return tupleMod != nullptr; }