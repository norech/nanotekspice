#include "../circuit/Circuit.hpp"
#include "../components/SpecialComponent.hpp"
#include "../components/Components.hpp"

#include <memory>
#include <iostream>

namespace nts {

std::unique_ptr<Circuit> Circuit::circuit;

Circuit::Circuit(void) {
    _factory["input"] = [](const std::string& n) { return std::make_unique<Input>(n); };
    _factory["clock"] = [](const std::string& n) { return std::make_unique<Clock>(n); };
    _factory["output"] = [](const std::string& n) { return std::make_unique<Output>(n); };
    _factory["true"] = [](const std::string& n) { return std::make_unique<True>(n); };
    _factory["false"] = [](const std::string& n) { return std::make_unique<False>(n); };
    _factory["4001"] = [](const std::string& n) { return std::make_unique<Component4001>(n); };
    _factory["4081"] = [](const std::string& n) { return std::make_unique<Component4081>(n); };
}

Circuit& Circuit::getInstance(void) {
    if (Circuit::circuit.get() == nullptr) circuit = std::make_unique<Circuit>();
    return *Circuit::circuit;
}

Component& Circuit::getFromName(const std::string& name) {
    Circuit& circuit = Circuit::getInstance();
    auto it = circuit._components.find(name);

    if (it == circuit._components.end())
        throw std::runtime_error(
            std::string("Circuit does not contain a component named ") +
            name
        );
    return *it->second;
}

bool Circuit::alreadyHasName(const std::string& name) {
    const auto& components = Circuit::getInstance()._components;
    return components.find(name) != components.end();
}

void Circuit::setLink(const std::string& leftComponent, std::size_t pinLeft, const std::string& rightComponent, std::size_t pinRight) {
    Component& left = Circuit::getFromName(leftComponent);
    Component& right = Circuit::getFromName(rightComponent);

    /*std::cout << "Circuit::setLink(" << leftComponent << ", "
              << pinLeft << ", " << rightComponent << ", "
              << pinRight << ")" << std::endl;*/

    if (left.getName() == right.getName()) {
        throw std::runtime_error("Cannot linked component to itself");
    }
    const auto& pin1 = left.getPin(pinLeft);
    const auto& pin2 = right.getPin(pinRight);
    /*if (pin1.getType() == pin2.getType()) {
        throw std::runtime_error("You can only link an Input with an output");
    }*/
    left.setLink(pinLeft, right, pinRight);
}

void Circuit::addComponent(const std::string& type,
                                 const std::string& name) {
    Circuit& circuit = Circuit::getInstance();

    if (circuit.alreadyHasName(name)) {
        throw std::runtime_error(
            "Cannot add twice a component with the same name");
    }
    if (circuit._factory.find(type) == circuit._factory.end()) {
        throw std::runtime_error(std::string("Unknown component type: ") + type);
    }
    circuit._components[name] = std::move(circuit._factory[type](name));
}

void Circuit::unvisit(void) {
    Circuit& circuit = Circuit::getInstance();

    for (auto& it : circuit._components) {
        for (auto& pin : it.second->getPins()) {
            pin.second->unvisit();
        }
    }
}

void Circuit::simulate(void) {
    Circuit& circuit = Circuit::getInstance();
    circuit._tick++;

    Circuit::unvisit();
    for (auto& it : circuit._components) {
        if (dynamic_cast<Output *>(it.second.get()) != nullptr)
            it.second->simulate();
    }
    for (auto& it : circuit._components) {
        it.second->simulate();
    }
}

void Circuit::dump(void) {
    Circuit& circuit = Circuit::getInstance();

    for (auto& it : circuit._components) {
        it.second->dump();
    }
}

template<typename T>
static void displayCircuitInfo(const std::string& name) {
    char state[2] = {'0', '1'};
    Circuit& circuit = Circuit::getInstance();

    std::cout << name << ": " << std::endl;
    for (auto& it : circuit.getComponents()) {
        T *in = dynamic_cast<T *>(it.second.get());
        if (in != nullptr) {
            auto cur_state = it.second->getPin(1).getState();
            std::cout << " " << it.second->getName() << ": " <<
                    ((cur_state == UNDEFINED) ? 'U' : state[static_cast<int>(cur_state)])
                    << std::endl;
        }
    }

}

void Circuit::display(void) {

    Circuit& circuit = Circuit::getInstance();

    std::cout << "tick: " << circuit._tick << std::endl;
    displayCircuitInfo<Input>("input(s)");
    displayCircuitInfo<Output>("output(s)");
}


const std::map<std::string, std::unique_ptr<Component>>& Circuit::getComponents() const { return _components; }

std::size_t Circuit::getTick(void) { return Circuit::getInstance()._tick; }
}  // namespace nts
