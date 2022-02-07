#pragma once

#include <string>

#include "../State.hpp"

namespace nts {

class IComponent {
public:
    IComponent();
    virtual ~IComponent() = default;

    virtual void simulate(std::size_t tick) = 0;
    virtual nts::Tristate compute(std::size_t pin) = 0;
    virtual void setLink(std::size_t pin, nts ::IComponent& other,
                         std::size_t otherPin) = 0;
    virtual void dump() const = 0;

private:
};

}  // namespace nts
