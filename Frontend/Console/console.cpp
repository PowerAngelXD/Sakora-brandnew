#include "console.h"


sakoraConsole::sakConsole::sakConsole() : instanceName("default"), cursor(0) {}
sakoraConsole::sakConsole::sakConsole(std::string name) : instanceName(name), cursor(0) {}

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

            Lexer::LexerInstance lexer;
            Lexer::TokenSequence sequence = lexer.startLexer(lineContent);

            // for(auto &token : sequence) {
            //     token.print();
            // }

            Parser p(sequence);

            if (p.isWholeExpr()) {
                auto ast = p.parseWholeExpr();
                std::cout<<ast->toString()<<std::endl;

                Generator gen;
                gen.generate(*ast);
            
                for (auto &ins : gen.insSet) {
                    ins.print();
                }

                vm.loadCodes(gen.insSet);
                vm.run();
            }
            else if (p.isStmt()) {
                auto asts = p.parse();
                
                Generator gen;
                for (auto ast : asts) {
                    std::cout<<ast->toString()<<std::endl;
                    gen.generate(*ast);
            
                    for (auto &ins : gen.insSet) {
                        ins.print();
                    }
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
