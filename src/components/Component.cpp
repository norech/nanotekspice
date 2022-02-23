#include "SpecialComponent.hpp"
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

    if (_pins[pin]->isLinkedTo(other, otherPin)) return;

    if (dynamic_cast<Input *>(this) != nullptr) {
        other.getPins()[otherPin]->setLink(*this, pin);
    } else {
        other.getPins()[otherPin]->setLink(*this, pin);
        this->getPins()[pin]->setLink(other, otherPin);
    }
    std::cout << "Component::setLink(" << getName() << ", "
              << pin << ", " << other.getName() << ", "
              << otherPin << ")" << std::endl;
}

Pin& Component::getPin(std::size_t pin) { return *_pins[pin]; }

const Component::PinMap& Component::getPins(void) const { return _pins; }

Component::PinMap& Component::getPins(void) { return _pins; }

std::size_t Component::getTick(void) const { return _tick; }

Component::Component(const std::string& name) : _name(name) {}

const std::string& Component::getName(void) const { return _name; }

void Component::simulate(std::size_t tick) {
    for (auto& it : _pins) {
        it.second->compute();
    }
}

void Component::dump(void) const {
    std::cout << "Dump: " << _name << std::endl;
    for (const auto& it : _pins) {
        std::cout << "pin" << std::to_string(it.first) << ": " << (int)it.second->getState() << std::endl;
    }
}

Tristate Component::compute(std::size_t pin) { return _pins[pin]->compute(); }

}  // namespace nts
