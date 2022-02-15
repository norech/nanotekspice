#include "Circuit.hpp"

namespace nts {
Chip& Chip::addOutputPin(IComponent *component,
                        std::size_t pin) {
    _pins[pin] = std::make_unique<OutputPin>(component, pin);
    return *this;
}

Chip& Chip::addInputPin(IComponent *component,
                       std::size_t pin) {
    _pins[pin] = std::make_unique<InputPin>(component, pin);
    return *this;
}

void Chip::link(std::size_t pin, std::shared_ptr<IComponent>& other,
                std::size_t otherPin) {
    if (_pins.find(pin) == _pins.end())
        throw std::runtime_error("Pin not found");
    else if (_pins[pin]->otherIsSelf(other))
        throw std::runtime_error("Cannot link to self");
    else if (_pins[pin]->getType() ==
             Circuit::getChip(other).getPinType(otherPin))
        throw std::runtime_error("Cannot link to same type");
    else
        _pins[pin]->setLink(other, otherPin);
}

void Chip::compute(void) {
    for (auto& pin : _pins) pin.second->compute();
}

PinType Chip::getPinType(std::size_t pin) const {
    return _pins.at(pin)->getType();
}

const std::map<std::size_t, std::unique_ptr<Pin>>& Chip::getPins(void) const {
    return _pins;
}
std::map<std::size_t, std::unique_ptr<Pin>>& Chip::getPins(void) {
    return _pins;
}

Pin& Chip::getPin(std::size_t pin) { return *_pins[pin]; }

}  // namespace nts