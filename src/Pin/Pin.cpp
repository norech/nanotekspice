#include "Pin.hpp"

#include <algorithm>
#include <iostream>

#include "../components/Component.hpp"
#include "../components/SpecialComponent.hpp"

namespace nts {
bool Pin::otherIsSelf(const Component &other) const {
    return &other == &_component;
}

bool Pin::isLinkedTo(const Component &other, std::size_t pin) const {
    for (const auto &it : _links) {
        if (&it->first == &other && it->second == pin) {
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
    if (_visited == false) return *this;
    _visited = false;
    for (auto &it : this->_component.getPins()) it.second->unvisit();
    for (auto &it : _links)
        for (auto &it2 : it->first.getPins()) it2.second->unvisit();
    return *this;
}

Tristate Pin::compute(void) {
    if (isVisited() == true) {
        return _state;
    }
    visit();
    std::erase_if(_links, [](const auto &it) {
        return it->first.getPin(it->second).isVisited();
    });
    Tristate tmp = UNDEFINED;
    for (auto &it : _links) {
        Tristate res = it->first.compute(it->second);
        if (tmp == UNDEFINED)
            tmp = res;
        else
            tmp = orGate(res, tmp);
    }
    if (dynamic_cast<Input *>(&this->_component) == nullptr) _state = tmp;
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
    if (isLinkedTo(other, otherPin)) {
        return;
    }
    _links.push_back(std::unique_ptr<Link>(new Link{other, otherPin}));
    other.getPin(otherPin).setLink(_component, _pin);
}

Component &Pin::getComponent(void) { return _component; }

std::size_t Pin::getPin(void) const { return _pin; }

}  // namespace nts
