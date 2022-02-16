#include "Component.hpp"

namespace nts {

Component& Component::addOutputPin(std::size_t pin) {
    _pins[pin] = std::make_unique<OutputPin>(this, pin);
    return *this;
}

Component& Component::addInputPin(std::size_t pin) {
    _pins[pin] = std::make_unique<InputPin>(this, pin);
    return *this;
}

void Component::setLink(std::size_t pin, IComponent& other,
                        std::size_t otherPin) {
    if (_pins[pin]->isLinkedTo(&other, otherPin)) return;
    _pins[pin]->setLink(&other, otherPin);
    other.setLink(otherPin, *this, pin);
}

Pin& Component::getPin(std::size_t pin) { return *_pins[pin]; }

const Component::PinMap& Component::getPins(void) const { return _pins; }

Component::PinMap& Component::getPins(void) { return _pins; }

Component::Component(const std::string& name) : _name(name) {}

const std::string& Component::getName(void) const { return _name; }
}  // namespace nts
