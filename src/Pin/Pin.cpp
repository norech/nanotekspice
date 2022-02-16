#include "Pin.hpp"

namespace nts {
bool Pin::otherIsSelf(const IComponent *other) const {
    return other == _component;
}

bool Pin::isLinkedTo(const IComponent *other, std::size_t pin) const {
    for (const auto it : _links) {
        if (it.first == other && it.second == pin) {
            return true;
        }
    }
    return false;
}

PinType Pin::getType(void) const { return _type; }

Pin::Pin(IComponent *component, std::size_t pin, PinType type)
    : _component(component), _pin(pin), _type(type) {}

OutputPin::OutputPin(IComponent *component, std::size_t pin)
    : Pin(component, pin, PinType::OUTPUT) {}
InputPin::InputPin(IComponent *component, std::size_t pin)
    : Pin(component, pin, PinType::INPUT) {}

void InputPin::setLink(IComponent *other, std::size_t otherPin) {
    _links.push_back(std::make_pair(other, otherPin));
}

void OutputPin::setLink(IComponent *other, std::size_t otherPin) {
    (void)other;
    (void)otherPin;
    throw std::runtime_error("Cannot link output");
}

}  // namespace nts
