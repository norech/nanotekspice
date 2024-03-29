#pragma once

#include <string>

#include "../Pin/Pin.hpp"
#include "../Tristate.hpp"

namespace nts {

class IComponent {
public:
    virtual ~IComponent() = default;

    virtual void simulate(void) = 0;
    virtual Tristate compute(std::size_t pin) = 0;
    virtual void setLink(std::size_t pin, IComponent& other,
                         std::size_t otherPin) = 0;
    virtual void dump() const = 0;
};

}  // namespace nts
