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
    std::cout << "Sakora REPL\nYou can type 'help' to get the help of this repl" << std::endl;

    sakVM vm;

    while (true) {
        try {
            std::string lineContent;

            std::cout << ">> ";
            std::getline(std::cin, lineContent);
            lineContent.push_back('\0');

            this->contentList.emplace_back(lineContent);
            this->cursor += 1;

            auto command = split(lineContent, ' ');
            if (command.at(0) == "run") {
                std::ifstream file(command.at(1));  
                std::string src((std::istreambuf_iterator<char>(file)),  
                                std::istreambuf_iterator<char>()); 

                src.push_back('\0');

                Lexer::LexerInstance lexer;
                auto lexerResult = lexer.startLexer(src);

                Parser parser(lexerResult);
                auto parserResult = parser.parse();

                Generator gen;
                for (auto stmt : parserResult) {
                    gen.generate(*stmt);
                }

                for (auto code : gen.insSet) {
                    std::cout << code.toString() << std::endl;
                }

                vm.loadCodes(gen.insSet);
                vm.run();
            }
            else {
                Lexer::LexerInstance lexer;
                auto lexerResult = lexer.startLexer(lineContent);

                Parser parser(lexerResult);
                auto parserResult = parser.parse();

                Generator gen;
                for (auto stmt : parserResult) {
                    gen.generate(*stmt);
                }

                for (auto code : gen.insSet) {
                    std::cout << code.toString() << std::endl;
                }

                vm.loadCodes(gen.insSet);
                vm.run();
            }
        }
        catch (SakoraError& e) {
            e.print();
        }
    }
}
