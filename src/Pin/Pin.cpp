#include "Pin.hpp"

namespace nts {
bool Pin::otherIsSelf(const std::shared_ptr<IComponent> &other) const {
    return other.get() == _component.get();
}

bool Pin::isLinkedTo(const std::shared_ptr<IComponent> &other,
                     std::size_t pin) const {
    for (const auto it : _links) {
        if (it.first.get() == other.get() && it.second == pin) {
            return true;
        }
    }
    return false;
}

PinType Pin::getType(void) const { return _type; }

Pin::Pin(std::shared_ptr<IComponent> &component, std::size_t pin, PinType type)
    : _component(component), _pin(pin), _type(type) {}

OutputPin::OutputPin(std::shared_ptr<IComponent> &component, std::size_t pin)
    : Pin(component, pin, PinType::OUTPUT) {}
InputPin::InputPin(std::shared_ptr<IComponent> &component, std::size_t pin)
    : Pin(component, pin, PinType::INPUT) {}

void InputPin::setLink(const std::shared_ptr<IComponent> &other,
                       std::size_t otherPin) {
    _links.push_back({other, otherPin});
}

void OutputPin::setLink(const std::shared_ptr<IComponent> &other,
                        std::size_t otherPin) {
    (void)other;
    (void)otherPin;
    throw std::runtime_error("Cannot link output");
}

}  // namespace nts
