#include <iostream>

#include "GatesComponent.hpp"
#include "../circuit/Circuit.hpp"

namespace nts {

Gate::Gate(const std::string& name) : Component(name) {}

DualInputGate::DualInputGate(
    const std::string& name,
    std::function<Tristate(const Tristate, const Tristate)> gate)
    : _gate(gate), Gate(name) {
    addInputPin(1).addInputPin(2).addOutputPin(3);
}

Tristate DualInputGate::compute(std::size_t pin) {
    std::cout << "DualInputGate::compute(" << getName() << ", " << pin << ")" << std::endl;
    if (pin == 3) {
        const auto p1 = compute(1);
        const auto p2 = compute(2);
        const auto res = _gate(p1, p2);
        std::cout << "DualInputGate::compute(" << getName() << ", "
                    << pin << ") = " << "p1: " << (int)p1 << ", p2: " << (int)p2
                    << ", res: " << (int)res << std::endl;
        return _pins[3]->update(res);
    }
    auto res = _pins[pin]->compute();
    return res;
}

And::And(void) : DualInputGate("AndGate", andGate) {}

Nand::Nand(void) : DualInputGate("NandGate", nandGate) {}

Xor::Xor(void) : DualInputGate("xorGate", xorGate) {}
Or::Or(void) : DualInputGate("Or", orGate) {}
Not::Not(void) : Gate("Not") {
    addInputPin(1).addOutputPin(2);
}

Tristate Not::compute(std::size_t pin) {
    std::cout << "Not::compute(" << getName() << ", " << pin << ")" << std::endl;
    if (pin == 1) {
        auto res = _pins[1]->compute();
        return res;
    }
    auto res = notGate(compute(1));
    return _pins[2]->update(res);
}

Nor::Nor(void) : Gate("Nor") {
    addInputPin(1).addInputPin(2).addOutputPin(3);

    this->setLink(1, *_or, 1);
    this->setLink(2, *_or, 2);
    _or->setLink(3, *_not, 1);
    _not->setLink(2, *this, 3);
}
}
