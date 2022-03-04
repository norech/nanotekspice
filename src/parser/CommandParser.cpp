#include "CommandParser.hpp"

#include <exception>
#include <sstream>

#include "../Error.hpp"
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
        throw RuntimeError("Invalid value");
    }
}

bool CommandParser::parseAssignation(Circuit& circuit, const std::string& cmd) {
    if (cmd.find("=") == std::string::npos) {
        return false;
    }
    std::string name = cmd.substr(0, cmd.find("="));
    std::string value = cmd.substr(cmd.find("=") + 1);

    // Just to throw an error in case of
    circuit.getFromName(name);

    _preSimulate.push({name, parseTristate(value)});
    return true;
}

void CommandParser::parseCommand(Circuit& circuit, const std::string& command) {
    std::stringstream ss(command);
    std::string cmd;
    ss >> cmd;
    if (cmd == "simulate") {
        for (; _preSimulate.empty() == false; _preSimulate.pop())
            circuit.setInput(_preSimulate.top().first,
                             _preSimulate.top().second);
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
        throw FatalError("exit");
    }
    else if (!parseAssignation(circuit, cmd)) {
        throw RuntimeError("Invalid command");
    }
}

}  // namespace nts
