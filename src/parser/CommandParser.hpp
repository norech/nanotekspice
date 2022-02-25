#pragma once

#include <stack>
#include <string>

#include "../circuit/Circuit.hpp"
#include "Tristate.hpp"

namespace nts {

class CommandParser {
public:
    CommandParser();
    ~CommandParser();
    CommandParser(const CommandParser& other) = default;
    CommandParser& operator=(const CommandParser& other) = default;

    void parseCommand(Circuit& circuit, const std::string& command);

private:
    bool parseAssignation(Circuit& circuit, const std::string& cmd);
    Tristate parseTristate(const std::string& state);

    std::stack<std::pair<std::string, Tristate>> _preSimulate;
};

}  // namespace nts
