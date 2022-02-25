#include "CommandParser.hpp"

#include <exception>
#include <sstream>

#include "../circuit/Circuit.hpp"
#include "../components/SpecialComponent.hpp"

namespace nts {

CommandParser::CommandParser() {}

CommandParser::~CommandParser() {}

Tristate CommandParser::parseTristate(const std::string& state) {
    if (state == "1") {
        return TRUE;
    }
    else if (state == "0") {
        return FALSE;
    }
    else if (state == "U") {
        return UNDEFINED;
    }
    else {
        throw std::runtime_error("Invalid value");
    }
}

bool CommandParser::parseAssignation(Circuit& circuit, const std::string& cmd) {
    if (cmd.find("=") == std::string::npos) {
        return false;
    }
    std::string name = cmd.substr(0, cmd.find("="));
    std::string value = cmd.substr(cmd.find("=") + 1);
    Component& comp = circuit.getFromName(name);
    Input* input = dynamic_cast<Input*>(&comp);
    if (input != nullptr) {
        input->setValue(parseTristate(value));
    }
    else {
        throw std::runtime_error("Cannot set value on a non-input component");
    }
    return true;
}

void CommandParser::parseCommand(Circuit& circuit, const std::string& command) {
    std::stringstream ss(command);
    std::string cmd;
    ss >> cmd;
    if (cmd == "simulate") {
        circuit.simulate();
    }
    else if (cmd == "display") {
        circuit.display();
    }
    else if (cmd == "loop") {
        while (true) {
            circuit.simulate();
            circuit.display();
        }
    }
    else if (cmd == "dump") {
        circuit.dump();
    }
    else if (cmd == "exit") {
        throw std::runtime_error("exit");
    }
    else if (!parseAssignation(circuit, cmd)) {
        throw std::runtime_error("Invalid command");
    }
}

}  // namespace nts
