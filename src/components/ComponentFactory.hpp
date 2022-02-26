#pragma once

#include "../circuit/Circuit.hpp"
#include "../components/Board.hpp"

namespace nts {

class ComponentFactory {
public:
    static Board* do4071();
    static Board* do4069();
};

}  // namespace nts
