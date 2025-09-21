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

    svm::VMInstance mainVM;

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

                auto start = std::chrono::high_resolution_clock::now();
                Lexer::LexerInstance lexer;
                auto lexerResult = lexer.startLexer(src);

                Parser parser(lexerResult);
                auto parserResult = parser.parse();

                sakora::Visitor visitor;
                for (auto stmt : parserResult) {
                    visitor.visit(*stmt);
                }

                for (auto code : visitor.seq) {
                    std::cout << code.toString() << std::endl;
                }

                mainVM.load(visitor.seq);

                mainVM.start();
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

                std::cout << "[Info] Execution finished in " << duration << " ms" << std::endl;
            }
            else {
                Lexer::LexerInstance lexer;
                auto lexerResult = lexer.startLexer(lineContent);

                Parser parser(lexerResult);
                auto parserResult = parser.parseWholeExpr();

                sakora::Visitor visitor;
                visitor.visit(*parserResult);

                for (auto code : visitor.seq) {
                    std::cout << code.toString() << std::endl;
                }

                mainVM.load(visitor.seq);
                mainVM.start(true);
            }
        }
        catch (SakoraError& e) {
            e.print();
        }
    }
}
