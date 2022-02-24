#include <iostream>

#include "src/parser/CommandParser.hpp"
#include "src/parser/FileParser.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 84;
    }

    try {
        nts::FileParser fp(argv[1]);
        nts::CommandParser cp;
        std::string cmd;

        fp.parse();
        std::cout << "> ";
        while (std::getline(std::cin, cmd)) {
            try {
                cp.parseCommand(cmd);
            } catch (std::runtime_error &e) {
                if (std::string(e.what()) == "exit") return 0;
                std::cerr << e.what() << std::endl;
            }
            std::cout << "> ";
        }
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
