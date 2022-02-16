#include "Component.hpp"

namespace nts {

    Component4030::Component4030(const std::string& name) : Component(name)
    {
        addInputPin(1);
        addInputPin(2);
        addInputPin(5);
        addInputPin(6);
        addInputPin(13);
        addInputPin(12);
        addInputPin(9);
        addInputPin(8);
        addOutputPin(11);
        addOutputPin(10);
        addOutputPin(3);
        addOutputPin(4);
    }

    Tristate Component4030::compute(std::size_t pin) {
        switch (pin) {
            case 11:
                return _pins[11]->update(xorGate(_pins[12]->compute(), _pins[13]->compute()));
            case 10:
                return _pins[10]->update(xorGate(_pins[9]->compute(), _pins[8]->compute()));
            case 4:
                return _pins[4]->update(xorGate(_pins[5]->compute(), _pins[6]->compute()));
            case 3:
                return _pins[3]->update(xorGate(_pins[1]->compute(), _pins[2]->compute()));
            default:
                return _pins[pin]->compute();
        }
    }
}
