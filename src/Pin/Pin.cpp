#include "Pin.hpp"

#include "../components/Component.hpp"

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

Tristate InputPin::compute(void) {
    if (isVisited()) return _state;
    visit();
    for (auto &it : _links) {
        it.first->simulate(_component->getTick());
        _state = orGate(_state, it.first->compute(it.second));
    }
    return _state;
}

Tristate OutputPin::compute(void) { return _component->compute(_pin); }

Tristate Pin::update(Tristate state) {
    setState(state);
    return getState();
}

Pin::Pin(IComponent *component, std::size_t pin, PinType type)
    : _component(component), _pin(pin), _type(type) {}

OutputPin::OutputPin(IComponent *component, std::size_t pin)
    : Pin(component, pin, PinType::OUTPUT) {}
InputPin::InputPin(IComponent *component, std::size_t pin)
    : Pin(component, pin, PinType::INPUT) {}

void Pin::setLink(IComponent *other, std::size_t otherPin) {
    _links.push_back(std::make_pair(other, otherPin));
}

}  // namespace nts
