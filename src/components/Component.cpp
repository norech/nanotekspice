#include "GatesComponent.hpp"
#include "../circuit/Circuit.hpp"
#include <iostream>

namespace nts {

Component& Component::addOutputPin(std::size_t pin) {
    _pins[pin] = std::make_unique<OutputPin>(*this, pin);
    return *this;
}

Component& Component::addInputPin(std::size_t pin) {
    _pins[pin] = std::make_unique<InputPin>(*this, pin);
    return *this;
}

void Component::setLink(std::size_t pin, IComponent& otherI,
                        std::size_t otherPin) {
    Component& other = dynamic_cast<Component&>(otherI);
    auto& it = getPin(pin);

    if (it.isLinkedTo(other, otherPin)) return;

    it.setLink(other, otherPin);
    /*std::cout << "Component::setLink(" << getName() << ", "
              << pin << ", " << other.getName() << ", "
              << otherPin << ")" << std::endl;*/
}

Pin& Component::getPin(std::size_t pin) {
    auto it = _pins.find(pin);

    if (it == _pins.end()) throw std::runtime_error(std::string("Cannot find pin: ") + std::to_string(pin));
    return *it->second;
}

const Component::PinMap& Component::getPins(void) const { return _pins; }

Component::PinMap& Component::getPins(void) { return _pins; }

Component::Component(const std::string& name) : _name(name) {}

const std::string& Component::getName(void) const { return _name; }

void Component::simulate(void) {
    for (auto& it : _pins) {
        if (it.second->getType() == OUTPUT) {
            it.second->getComponent().compute(it.first);
        }
    }
    for (auto& it : _pins) {
        it.second->getComponent().compute(it.first);
    }
}

void Component::dump(void) const {
    std::cout << "Dump: " << _name << std::endl;
    for (const auto& it : _pins) {
        std::cout << "pin" << std::to_string(it.first) << ": " << (int)it.second->getState() << std::endl;
    }
}

Tristate Component::compute(std::size_t pin) {
    //std::cout << "Component::compute(" << getName() << ", " << pin << ")" << std::endl;
    auto& it = getPin(pin);
    return it.compute();
}

}  // namespace nts
