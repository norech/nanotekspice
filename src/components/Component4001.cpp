#include "Component.hpp"

namespace nts {

Component4001::Component4001(const std::string& name) : Component(name) {
    addInputPin(1);
    addInputPin(2);
    addInputPin(5);
    addInputPin(6);
    addInputPin(8);
    addInputPin(9);
    addInputPin(12);
    addInputPin(13);
    addOutputPin(3);
    addOutputPin(4);
    addOutputPin(10);
    addOutputPin(11);
}

Tristate Component4001::compute(std::size_t pin) {
    switch (pin) {
        case 3:
            return _pins[3]->update(
                nts::xorGate(_pins[1]->compute(), _pins[2]->compute()));
        case 4:
            return _pins[4]->update(
                nts::xorGate(_pins[5]->compute(), _pins[6]->compute()));
        case 10:
            return _pins[4]->update(
                nts::xorGate(_pins[8]->compute(), _pins[9]->compute()));
        case 11:
            return _pins[4]->update(
                nts::xorGate(_pins[12]->compute(), _pins[13]->compute()));
        default:
            return _pins[pin]->compute();
    }
}



}  // namespace nts
