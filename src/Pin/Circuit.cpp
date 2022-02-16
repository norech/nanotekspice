#include "Circuit.hpp"

namespace nts {
Circuit *Circuit::circuit = nullptr;

Circuit::Circuit(void) {
    if (circuit == nullptr) circuit = this;
}

Circuit *Circuit::getInstance(void) { return Circuit::circuit; }

IComponent *Circuit::addChip(IComponent *component) {
    Circuit *circuit = Circuit::getInstance();

    for (auto &chip : circuit->_components) {
        if (chip.first.get() == component)
            throw std::runtime_error("Cannot add same component twice");
    }
    auto sp = std::make_unique<IComponent>(component);
    circuit->_chips[sp] = std::make_shared<Chip>();
    return *circuit->_chips[sp];
}

Chip &Circuit::getChip(IComponent *component) {
    Circuit *circuit = Circuit::getInstance();

    for (auto &chip : circuit->_chips) {
        if (chip.first.get() == component) return *chip.second;
    }
    throw std::runtime_error("Component not found");
}


}  // namespace nts
