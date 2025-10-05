#pragma GCC optimize(3,"Ofast","inline")
#include "console.h"


sakoraConsole::sakConsole::sakConsole() : instanceName("default"), cursor(0) {}
sakoraConsole::sakConsole::sakConsole(std::string name) : instanceName(name), cursor(0) {}

std::vector<std::string> sakoraConsole::sakConsole::split(std::string raw, char c) {
    std::vector<std::string> result;
    std::istringstream iss(raw);
	std::string token;
	while (std::getline(iss, token, c))	{
		result.push_back(token);
	}
    return result;
}

void sakoraConsole::sakConsole::run() {
    std::cout << "GCC Version: " <<  __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
    std::cout << "Sakora REPL\nYou can type 'help' to get the help of this repl" << std::endl;

    while (true) {
        try {
            std::string lineContent;

            std::cout << ">> ";
            std::getline(std::cin, lineContent);
            lineContent.push_back('\0');

            this->contentList.emplace_back(lineContent);
            this->cursor += 1;

            auto command = split(lineContent, ' ');
            
        }
        catch (SakoraError& e) {
            e.print();
        }
    }
}
