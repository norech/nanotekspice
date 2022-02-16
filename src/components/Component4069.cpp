#include "Component.hpp"

namespace nts
{
    Component4069::Component4069(const std::string& name) : Component(name)
    {
        addInputPin(1);
        addInputPin(3);
        addInputPin(5);
        addInputPin(13);
        addInputPin(11);
        addInputPin(9);
        addOutputPin(12);
        addOutputPin(10);
        addOutputPin(8);
        addOutputPin(2);
        addOutputPin(4);
        addOutputPin(6);
    }

    Tristate Component4069::compute(std::size_t pin) {
        switch (pin) {
        case 2:
            return _pins[2]->update(notGate(_pins[1]->compute()));
        case 4:
            return _pins[4]->update(notGate(_pins[3]->compute()));
        case 6:
            return _pins[6]->update(notGate(_pins[5]->compute()));
        case 12:
            return _pins[12]->update(notGate(_pins[13]->compute()));
        case 10:
            return _pins[10]->update(notGate(_pins[11]->compute()));
        case 8:
            return _pins[8]->update(notGate(_pins[9]->compute()));
        default:
            return _pins[pin]->compute();
        }
    }
}
