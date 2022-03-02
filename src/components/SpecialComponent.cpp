#include "SpecialComponent.hpp"

#include <iostream>

namespace nts {
SpecialComponent::SpecialComponent(const std::string& name) : Component(name) {}

Tristate SpecialComponent::compute(std::size_t pin) {
    // std::cout << "SpecialComponent::compute(" << getName() << ")" <<
    // std::endl;
    auto& it = getPin(pin);
    if (dynamic_cast<Output*>(this)) {
        return it.compute();
    }
    return it.getState();
}

void SpecialComponent::simulate(void) {
    // std::cout << "SpecialComponent::simulate(" << getName() << ")" <<
    // std::endl;
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

void Clock::onPinChanged(size_t pin) {
    if (pin == 1) {
        _alreadyInvertedOnce = false;
    }
}

Output::Output(const std::string& name) : SpecialComponent(name) {
    addInputPin(1);
}

True::True(const std::string& name) : SpecialComponent(name) {
    addOutputPin(1);
    getPin(1).setState(TRUE);
}

Tristate True::compute(size_t pin) { return TRUE; }

False::False(const std::string& name) : SpecialComponent(name) {
    addOutputPin(1);
    getPin(1).setState(FALSE);
}

Tristate False::compute(size_t pin) { return FALSE; }

};  // namespace nts
