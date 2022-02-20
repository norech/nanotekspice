#include "../circuit/Circuit.hpp"

#include <memory>

namespace nts {

std::unique_ptr<Circuit> Circuit::circuit = nullptr;

Circuit::Circuit(void) {
}

Circuit& Circuit::getInstance(void) {
    if (Circuit::circuit == nullptr) circuit = std::make_unique<Circuit>();
    return *Circuit::circuit;
}

Component* Circuit::getFromName(const std::string& name) {
    Circuit& circuit = Circuit::getInstance();

    for (auto& it : circuit._components) {
        if (it->getName() == name) return it.get();
    }
    return nullptr;
}

Component* Circuit::addComponent(const std::string& type,
                                 const std::string& name) {
    Circuit& circuit = Circuit::getInstance();

    if (circuit.getFromName(name) != nullptr) {
        throw std::runtime_error(
            "Cannot add twice a component with the same name");
    }
    throw std::runtime_error("No component can be added yet");
}

void Circuit::unvisit(void) {
    Circuit& circuit = Circuit::getInstance();

    for (auto& it : circuit._components) {
        for (auto& pin : it->getPins()) {
            pin.second->unvisit();
        }
    }
}

void Circuit::simulate(void) {
    Circuit& circuit = Circuit::getInstance();
    Circuit::unvisit();
    circuit._tick++;
    for (auto& it : circuit._components) {
        it->simulate(circuit._tick);
    }
}

std::size_t Circuit::getTick(void) const { return _tick; }
}  // namespace nts
