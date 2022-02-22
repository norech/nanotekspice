#pragma once

#include <fstream>
#include <string>

#include "../circuit/Circuit.hpp"

namespace nts {

class FileParser {
public:
    FileParser(const std::string& file);
    ~FileParser();
    FileParser(const FileParser& other) = default;
    FileParser& operator=(const FileParser& other) = default;

    Circuit& parse();

private:
    std::ifstream _stream;
    std::string _line;
    void parseChipsets();
    void parseLinks();
};

}  // namespace nts
