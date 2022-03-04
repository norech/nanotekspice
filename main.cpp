#include <iostream>

#include "src/Error.hpp"
#include "src/circuit/Circuit.hpp"
#include "src/parser/CircuitParser.hpp"
#include "src/parser/CommandParser.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 84;
    }

    try {
        nts::CircuitParser circuitParser(argv[1]);
        nts::CommandParser cp;
        std::string cmd;

        std::unique_ptr<nts::Circuit> circuit =
            std::unique_ptr<nts::Circuit>(circuitParser.parse());
        std::cout << "> ";
        while (std::getline(std::cin, cmd)) {
            try {
                cp.parseCommand(*circuit, cmd);
            } catch (nts::RuntimeError &e) {
                if (std::string(e.what()) == "exit") return 0;
                std::cerr << e.what() << std::endl;
            }
            std::cout << "> ";
        }
    } catch (nts::Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (std::exception &e) {
        std::cerr << "Internal error: " << e.what() << std::endl;
        return 84;
    }
}
