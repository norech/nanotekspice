#pragma once

#include <string>

#include "Tristate.hpp"

namespace nts {

class CommandParser {
public:
    CommandParser();
    ~CommandParser();
    CommandParser(const CommandParser& other) = default;
    CommandParser& operator=(const CommandParser& other) = default;

    void parseCommand(const std::string& command);

private:
    bool parseAssignation(const std::string& cmd);
    Tristate parseTristate(const std::string& state);
};

}  // namespace nts
