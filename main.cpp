#include "Frontend/Console/console.h"
#include <memory>

int main() {
    sakoraConsole::sakConsole console("official");

    console.run();

    return 0;
}