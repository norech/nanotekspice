#include "GatesComponent.hpp"

#include <iostream>

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
    // std::cout << "DualInputGate::compute(" << getName() << ", " << pin << ")"
    // << std::endl;
    if (pin == 3) {
        const auto p1 = compute(1);
        const auto p2 = compute(2);
        const auto res = _gate(p1, p2);
        /*std::cout << "DualInputGate::compute(" << getName() << ", "
                    << pin << ") = " << "p1: " << (int)p1 << ", p2: " << (int)p2
                    << ", res: " << (int)res << std::endl;*/
        return _pins[3]->update(res);
    }
    auto res = _pins[pin]->compute();
    return res;
}

And::And(void) : DualInputGate("AndGate", andGate) {}

Xor::Xor(void) : DualInputGate("xorGate", xorGate) {}
Or::Or(void) : DualInputGate("Or", orGate) {}

Not::Not(void) : Gate("Not") { addInputPin(1).addOutputPin(2); }

Tristate Not::compute(std::size_t pin) {
    // std::cout << "Not::compute(" << getName() << ", " << pin << ")" <<
    // std::endl;
    if (pin == 1) {
        auto res = _pins[1]->compute();
        return res;
    }
    auto res = notGate(compute(1));
    return _pins[2]->update(res);
}

    FullAdder::FullAdder(const std::string& name) : Gate(name) {
        addInputPin(1).addInputPin(2).addInputPin(3).addOutputPin(4).addOutputPin(5);

        _inputLinker->setLink(1, *this, 1);
        _inputLinker->setLink(2, *this, 2);
        _inputLinker->setLink(3, *_xorResult, 1);
        _inputLinker->setLink(3, *_linker1, 1);

        _xorResult->setLink(1, *_inputLinker, 3);
        _xorResult->setLink(2, *this, 3);
        _xorResult->setLink(3, *this, 4);

        _linker1->setLink(1, *_inputLinker, 3);
        _linker1->setLink(2, *this, 3);
        _linker1->setLink(3, *_orResult, 1);

        _linker2->setLink(1, *this, 1);
        _linker2->setLink(2, *this, 2);
        _linker2->setLink(3, *_orResult, 2);

        _orResult->setLink(1, *_linker1, 3);
        _orResult->setLink(2, *_linker2, 3);
        _orResult->setLink(3, *this, 5);
    }

}  // namespace nts
