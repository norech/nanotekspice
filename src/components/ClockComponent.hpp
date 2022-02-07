#pragma once

#include "InputComponent.hpp"

namespace nts {

class ClockComponent : public InputComponent {
public:
    ClockComponent();
    ~ClockComponent();

    void simulate(std::size_t tick) final;
};

} // namespace nts
