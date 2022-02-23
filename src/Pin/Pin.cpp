#include "Pin.hpp"
#include <iostream>

#include "../components/Component.hpp"

namespace nts {
bool Pin::otherIsSelf(const Component &other) const {
    return &other == &_component;
}

bool Pin::isLinkedTo(const Component &other, std::size_t pin) const {
    for (const auto it : _links) {
        if (&it.first == &other && it.second == pin) {
            return true;
        }
    }
    return false;
}

PinType Pin::getType(void) const { return _type; }
Tristate Pin::getState(void) const { return _state; }
Pin &Pin::setState(Tristate state) {
    _state = state;
    return *this;
}

bool Pin::isVisited(void) const { return _visited; }
Pin &Pin::visit(void) {
    _visited = true;
    return *this;
}
Pin &Pin::unvisit(void) {
    _visited = false;
    return *this;
}

Tristate Pin::compute(void) {
    std::cout << "B: " << _component.getName() << " -> " << _state << std::endl;
    if (isVisited()) {
        std::cout << "A: " << _component.getName() << " -> " << _state << std::endl;
        return _state;
    }
    visit();
    std::cout << _links.size() << std::endl;
    for (auto &it : _links) {
        std::cout << "\tComputing " << it.first.getName() << std::endl;
        _state = orGate(_state, it.first.compute(it.second));
    }
    std::cout << "C: " << _component.getName() << " -> " << _state << std::endl;
    return _state;
}

Tristate Pin::update(Tristate state) {
    setState(state);
    return getState();
}

Pin::Pin(Component &component, std::size_t pin, PinType type)
    : _component(component), _pin(pin), _type(type) {}

OutputPin::OutputPin(Component &component, std::size_t pin)
    : Pin(component, pin, PinType::OUTPUT) {}
InputPin::InputPin(Component &component, std::size_t pin)
    : Pin(component, pin, PinType::INPUT) {}

void Pin::setLink(Component &other, std::size_t otherPin) {
    _links.push_back(
        {other, otherPin}
    );
}

}  // namespace nts
