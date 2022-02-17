#include "Pin.hpp"

#include "../components/Component.hpp"

namespace nts {
bool Pin::otherIsSelf(const Component &other) const {
    return &other == &_component.get();
}

bool Pin::isLinkedTo(const Component &other, std::size_t pin) const {
    for (const auto it : _links) {
        if (&it.first.get() == &other && it.second == pin) {
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
    if (isVisited()) return _state;
    visit();
    for (auto &it : _links) {
        if (&it.first.get() != &_component.get()) {
            it.first.get().simulate(_component.get().getTick());
        }
        _state = orGate(_state, it.first.get().compute(it.second));
    }
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
        std::make_pair(std::reference_wrapper<Component>(other), otherPin));
}

}  // namespace nts
