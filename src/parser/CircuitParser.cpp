#include "CircuitParser.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>

#include "../circuit/Circuit.hpp"
#include "../components/Component.hpp"

namespace nts {

CircuitParser::CircuitParser(const std::string& file)
    : _circuit(new Circuit(file)) {
    _stream.open(file);
    if (!_stream || _stream.bad()) {
        throw std::runtime_error("Error: cannot open input file");
    }
}

CircuitParser::~CircuitParser() {}

static inline std::string trim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
                return !std::isspace(c);
            }));
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char c) { return !std::isspace(c); })
                .base(),
            s.end());
    return s;
}

void CircuitParser::parseChipsets() {
    while (std::getline(_stream, _line)) {
        _line = trim(_line.substr(0, _line.find('#')));
        if (_line.empty()) continue;
        if (_line.find(".") == 0) break;
        std::stringstream ss(_line);
        std::string type;
        std::string name;
        ss >> type >> name;
        if (ss.bad() || type.empty() || name.empty()) {
            throw std::runtime_error("Error: invalid chipset '" + _line + "'");
        }
        _circuit->addComponent(type, name);
    }
}

void CircuitParser::parseLinks() {
    while (std::getline(_stream, _line)) {
        _line = trim(_line.substr(0, _line.find('#')));
        if (_line.empty()) continue;
        if (_line.find(".") == 0) break;
        std::stringstream ss(_line);
        std::string pinPair1;
        std::string pinPair2;
        ss.clear();
        ss >> pinPair1 >> pinPair2;
        if (ss.bad() || pinPair1.find(":") == std::string::npos ||
            pinPair2.find(":") == std::string::npos) {
            throw std::runtime_error("Error: invalid link '" + _line + "'");
        }

        const std::string name1 = pinPair1.substr(0, pinPair1.find(':'));
        const std::string pin1 = pinPair1.substr(pinPair1.find(':') + 1);
        const std::string name2 = pinPair2.substr(0, pinPair2.find(':'));
        const std::string pin2 = pinPair2.substr(pinPair2.find(':') + 1);

        std::stringstream ssPin1(pin1);
        std::stringstream ssPin2(pin2);
        int pin1Int;
        int pin2Int;
        ssPin1 >> pin1Int;
        ssPin2 >> pin2Int;
        if (name1.empty() || name2.empty() || ssPin1.bad() || ssPin2.bad()) {
            throw std::runtime_error("Error: invalid pin link '" + _line + "'");
        }

        _circuit->setLink(name1, pin1Int, name2, pin2Int);
    }
}

Circuit* CircuitParser::parse() {
    while (std::getline(_stream, _line)) {
        _line = trim(_line.substr(0, _line.find('#')));

        if (_line.empty()) continue;
        if (_line.find(".chipsets:") == 0) {
            parseChipsets();
        }
        if (_line.find(".links:") == 0) {
            parseLinks();
        }
    }
    return _circuit;
}

}  // namespace nts
