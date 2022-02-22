#include <iostream>

#include "src/parser/FileParser.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    nts::FileParser fp(argv[1]);

    fp.parse();
}
