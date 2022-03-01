#include "../circuit/Circuit.hpp"

#include <string.h>

#include <iostream>
#include <memory>

#include "../components/Board.hpp"
#include "../components/Component.hpp"
#include "../components/ComponentFactory.hpp"
#include "../components/Components.hpp"
#include "../components/SpecialComponent.hpp"
#include "../parser/CircuitParser.hpp"

namespace nts {

Circuit::Circuit(const std::string& name) : _name(name) {
    _factory.insert(NTS_COMPONENT_FACTORY("_or", Or));
    _factory.insert(NTS_COMPONENT_FACTORY("_not", Not));
    _factory.insert(NTS_COMPONENT_FACTORY("input", Input));
    _factory.insert(NTS_COMPONENT_FACTORY("clock", Clock));
    _factory.insert(NTS_COMPONENT_FACTORY("output", Output));
    _factory.insert(NTS_COMPONENT_FACTORY("true", True));
    _factory.insert(NTS_COMPONENT_FACTORY("false", False));
    _factory.insert(NTS_COMPONENT_FACTORY("4001", Component4001));
    _factory.insert(NTS_COMPONENT_FACTORY("4008", Component4008));
    _factory.insert(NTS_COMPONENT_FACTORY("4011", Component4011));
    _factory.insert(NTS_COMPONENT_FACTORY("4030", Component4030));
    //_factory.insert(NTS_COMPONENT_FACTORY("4071", Component4071));
    _factory.insert(NTS_COMPONENT_FACTORY_FN("4071", ComponentFactory::do4071));
    _factory.insert(NTS_COMPONENT_FACTORY_FN("4069", ComponentFactory::do4069));
    _factory.insert(NTS_COMPONENT_FACTORY("4081", Component4081));

    _factory.insert(NTS_COMPONENT_FACTORY("HalfAdder", HalfAdder));
    _factory.insert(NTS_COMPONENT_FACTORY("FullAdder", FullAdder));
}

Component& Circuit::getFromName(const std::string& name) {
    auto it = _components.find(name);

    if (it == _components.end())
        throw std::runtime_error(std::string("Circuit '") + _name +
                                 "' does not contain a component named " +
                                 name);
    return *it->second;
}

bool Circuit::alreadyHasName(const std::string& name) {
    return _components.find(name) != _components.end();
}

void Circuit::setLink(const std::string& leftComponent, std::size_t pinLeft,
                      const std::string& rightComponent, std::size_t pinRight) {
    Component& left = Circuit::getFromName(leftComponent);
    Component& right = Circuit::getFromName(rightComponent);

    /*std::cout << "Circuit::setLink(" << leftComponent << ", "
              << pinLeft << ", " << rightComponent << ", "
              << pinRight << ")" << std::endl;*/

    // NOTE: this cannot work because of the requirements
    /*if (left.getName() == right.getName()) {
        throw std::runtime_error("Cannot linked component to itself");
    }*/
    const auto& pin1 = left.getPin(pinLeft);
    const auto& pin2 = right.getPin(pinRight);

    if (pin1.getType() == OUTPUT && pin2.getType() == INPUT) {
        right.setLink(pinRight, left, pinLeft);
    }
    else if (pin1.getType() == INPUT && pin2.getType() == OUTPUT) {
        left.setLink(pinLeft, right, pinRight);
    }
    else {
        throw std::runtime_error(
            std::string("Cannot link two pins of the same type '") +
            leftComponent + " " + std::to_string(pin1.getPin()) + "' and '" +
            rightComponent + " " + std::to_string(pin2.getPin()) + "'" +
            " -> type is " + (pin1.getType() == INPUT ? "Input" : "Output"));
    }
}

void Circuit::addComponent(const std::string& type, const std::string& name) {
    if (alreadyHasName(name)) {
        throw std::runtime_error(
            "Cannot add twice a component with the same name");
    }
    if (_factory.find(type) == _factory.end()) {
        throw std::runtime_error(std::string("Unknown component type: ") +
                                 type);
    }
    _components[name] = std::move(_factory[type](name));
}

void Circuit::unvisit(void) {
    for (auto& it : _components) {
        for (auto& pin : it.second->getPins()) {
            pin.second->unvisit();
        }
    }
}

void Circuit::simulate(void) {
    _tick++;

    Circuit::unvisit();
    for (auto& it : _components) {
        // if (dynamic_cast<Output*>(it.second.get()) != nullptr)
        it.second->simulate();
    }
}

void Circuit::dump(void) {
    Circuit& circuit = *this;

    for (auto& it : _components) {
        it.second->dump();
    }
}

template <typename T>
void displayCircuitInfo(Circuit& circuit, const std::string& name) {
    char state[2] = {'0', '1'};

    std::cout << name << ":" << std::endl;

    std::vector<std::pair<std::string, char>> states;

    for (auto& it : circuit.getComponents()) {
        T* in = dynamic_cast<T*>(it.second.get());
        if (in != nullptr) {
            auto cur_state = it.second->getPin(1).getState();
            states.push_back(std::make_pair(
                it.second->getName(),
                cur_state == UNDEFINED ? 'U'
                                       : state[static_cast<int>(cur_state)]));
        }
    }
    std::sort(states.begin(), states.end());
    for (auto& it : states) {
        std::cout << "  " << it.first << ": " << it.second << std::endl;
    }
}

void Circuit::display(void) {
    std::cout << "tick: " << _tick << std::endl;
    displayCircuitInfo<Input>(*this, "input(s)");
    displayCircuitInfo<Output>(*this, "output(s)");
}

const std::map<std::string, std::unique_ptr<Component>>& Circuit::getComponents(
    void) const {
    return _components;
}

std::size_t Circuit::getTick(void) { return _tick; }

void Circuit::setInput(const std::string& name, Tristate value) {
    /*
    std::cerr << "Circuit::setInput(" << name << ", " << value << ")"
              << std::endl;
    */
    Component* comp = &getFromName(name);
    // std::cerr << "component: " << comp->getName() << std::endl;
    Input* in = dynamic_cast<Input*>(comp);

    if (in == nullptr)
        throw std::runtime_error(std::string("Component ") + name +
                                 " is not an input");
    in->getPin(1).setState(value);
}

Tristate Circuit::getOutput(const std::string& name) {
    Component* comp = &getFromName(name);
    Output* out = dynamic_cast<Output*>(comp);

    if (out == nullptr)
        throw std::runtime_error(std::string("Component ") + name +
                                 " is not an output");
    return out->getPin(1).getState();
}

const std::string& Circuit::getName(void) const { return _name; }

}  // namespace nts
