#pragma once

#include <string>

#include "../Pin/Pin.hpp"
#include "../Tristate.hpp"

namespace nts {

class IComponent {
public:
    virtual ~IComponent() = default;

    virtual void simulate(std::size_t tick) = 0;
    virtual Tristate compute(std::size_t pin) = 0;
    virtual void setLink(std::size_t pin, IComponent& other,
                         std::size_t otherPin) = 0;
    virtual void dump() const = 0;
    virtual std::size_t getTick() const = 0;
    virtual void reset() = 0;
};

}  // namespace nts
