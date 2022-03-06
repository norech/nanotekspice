#include <iostream>

#include "src/Error.hpp"
#include "src/circuit/Circuit.hpp"
#include "src/parser/CircuitParser.hpp"
#include "src/parser/CommandParser.hpp"

void runNTS(const std::string &circuitPath) {
    nts::CircuitParser circuitParser(circuitPath);
    nts::CommandParser commandParser;
    std::unique_ptr<nts::Circuit> circuit(circuitParser.parse());
    std::string cmd;

    std::cout << "> ";
    while (std::getline(std::cin, cmd)) {
        try {
            commandParser.parseCommand(*circuit, cmd);
        } catch (nts::RuntimeError &e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "> ";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 84;
    }

    try {
        runNTS(argv[1]);
    } catch (nts::Error &e) {
        if (std::string(e.what()) == "exit") return 0;
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (std::exception &e) {
        std::cerr << "Internal error: " << e.what() << std::endl;
        return 84;
    }
}
