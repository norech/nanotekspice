#pragma once

#include "../circuit/Circuit.hpp"
#include "../gates/Gates.hpp"
#include "./Component.hpp"

namespace nts {

class Board : public Component {
private:
    std::unique_ptr<nts::Circuit> _circuit;

protected:
public:
    Board(Circuit *circuit);

    Tristate compute(std::size_t pin) override;
};

}  // namespace nts
