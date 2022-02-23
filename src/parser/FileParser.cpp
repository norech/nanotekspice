#include "FileParser.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>

#include "../circuit/Circuit.hpp"
#include "../components/Component.hpp"

namespace nts {

FileParser::FileParser(const std::string &file) {
    _stream.open(file);
    if (!_stream || _stream.bad()) {
        throw std::runtime_error("Error: cannot open input file");
    }
}

FileParser::~FileParser() {}

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

void FileParser::parseChipsets() {
    std::vector<Component> chipsets;

    while (std::getline(_stream, _line)) {
        _line = trim(_line.substr(0, _line.find('#')));
        if (_line.empty()) continue;
        if (_line.find(".") == 0) break;
        std::stringstream ss(_line);
        std::string type;
        std::string name;
        ss >> type >> name;
        Circuit::addComponent(type, name);
        std::cerr << "Chipset: " << type << ", name: " << name << std::endl;
    }
}

void FileParser::parseLinks() {
    while (std::getline(_stream, _line)) {
        _line = trim(_line.substr(0, _line.find('#')));
        if (_line.empty()) continue;
        if (_line.find(".") == 0) break;
        std::stringstream ss(_line);
        std::string pinPair1;
        std::string pinPair2;
        ss >> pinPair1 >> pinPair2;
        std::cerr << pinPair1 << " linked to " << pinPair2 << std::endl;
    }
}

Circuit &FileParser::parse() {
    while (std::getline(_stream, _line)) {
        _line = trim(_line.substr(0, _line.find('#')));

        if (_line.empty()) continue;
        if (_line.find(".chipsets:") == 0) {
            std::cerr << "lol chipset" << std::endl;
            parseChipsets();
        }
        if (_line.find(".links:") == 0) {
            parseLinks();
        }
    }
    return Circuit::getInstance();
}

}  // namespace nts
