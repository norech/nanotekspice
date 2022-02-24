#include "SpecialComponent.hpp"
#include <iostream>

namespace nts {
SpecialComponent::SpecialComponent(const std::string& name) : Component(name) { }

Tristate SpecialComponent::compute(std::size_t pin) {
    //std::cout << "SpecialComponent::compute(" << getName() << ")" << std::endl;
    auto& it = getPin(pin);
    return it.compute();
}

void SpecialComponent::simulate(void) {
    //std::cout << "SpecialComponent::simulate(" << getName() << ")" << std::endl;
    _pins[1]->compute();
}

Input::Input(const std::string& name) : SpecialComponent(name) {
    addOutputPin(1);
}

void Input::setValue(Tristate value) { _pins[1]->setState(value); }

Clock::Clock(const std::string& name) : Input(name) {}

void Clock::simulate(void) {
    auto& it = _pins[1];
    if (it->getState() == Tristate::UNDEFINED) {
        return;
    }
    else if (it->getState() == Tristate::FALSE) {
        it->setState(Tristate::TRUE);
    }
    else {
        it->setState(Tristate::FALSE);
    }
}

Output::Output(const std::string& name) : SpecialComponent(name) {
    addInputPin(1);
}

Boolean::Boolean(const std::string& name, bool value) : SpecialComponent(name) {
    addOutputPin(1);
    _pins[1]->setState(value ? TRUE : FALSE);
}

True::True(const std::string& name) : Boolean(name, true) {}

False::False(const std::string& name) : Boolean(name, false) {}
};  // namespace nts
