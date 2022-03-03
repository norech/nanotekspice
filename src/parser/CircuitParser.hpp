#pragma once

#include <fstream>
#include <string>

#include "../Error.hpp"
#include "../circuit/Circuit.hpp"

namespace nts {

class CircuitParser {
public:
    CircuitParser(const std::string& file);
    ~CircuitParser();
    CircuitParser(const CircuitParser& other) = default;
    CircuitParser& operator=(const CircuitParser& other) = default;

    Circuit* parse();

private:
    std::ifstream _stream;
    std::string _line;
    void parseChipsets();
    void parseLinks();
    Circuit* _circuit;
};

}  // namespace nts
