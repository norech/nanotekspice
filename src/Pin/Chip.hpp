#pragma once

#include <map>

#include "Pin.hpp"

namespace nts {
class Chip : public IComponent {
private:
    std::map<size_t, std::unique_ptr<Pin>> _pins;

public:
    Chip(void) = default;
    ~Chip(void) = default;

    Chip& addOutputPin(IComponent* component, std::size_t pin);

    Chip& addInputPin(IComponent* component, std::size_t pin);

    void link(std::size_t pin, std::shared_ptr<IComponent>& other,
              std::size_t otherPin);

    void compute(void);

    PinType getPinType(std::size_t pin) const;

    const std::map<std::size_t, std::unique_ptr<Pin>>& getPins(void) const;

    std::map<std::size_t, std::unique_ptr<Pin>>& getPins(void);

    Pin& getPin(std::size_t pin);
};
}  // namespace nts
