#include "Component.hpp"
#include <iostream>

namespace nts {

    class Gate : public Component {
    protected:
        Gate(const std::string& name) : Component(name) {}
    };

    class DualInputGate : public Gate {
    private:
        std::function<Tristate(const Tristate, const Tristate)> _gate;

    protected:
        DualInputGate(const std::string& name,
            std::function<Tristate(const Tristate, const Tristate)> gate
        ) :
        _gate(gate), Gate(name) {
            addInputPin(1).addInputPin(2).addOutputPin(3);
            setLink(1, *this, 3);
            setLink(2, *this, 3);
        }

    public:
        Tristate compute(std::size_t pin) override {
            if (pin == 3) {
                return _pins[3]->update(_gate(_pins[1]->compute(), _pins[2]->compute()));
            }
            return _pins[pin]->compute();
        }

    };

    class And : public DualInputGate {
    public:
        And(void) : DualInputGate("AndGate", andGate) {}
    };

    class Nand : public DualInputGate {
    public:
        Nand(void) : DualInputGate("NandGate", nandGate) {}
    };

    class Xor : public DualInputGate {
    public:
        Xor(void) : DualInputGate("xorGate", xorGate) {}
    };

    class Or : public DualInputGate {
    public:
        Or(void) : DualInputGate("Or", orGate) {}
    };

    class Not : public Gate {
    public:
        Not(void) : Gate("Not") {
            addInputPin(1).addOutputPin(2);
            setLink(1, *this, 2);
        }

        Tristate compute(std::size_t pin) override {
            auto res = _pins[pin]->compute();

            if (pin == 2) {
                return _pins[2]->update(notGate(res));
            }
            return res;
        }

    };

    class Nor : public Gate {
    private:
        std::unique_ptr<Or> _or = std::make_unique<Or>();
        std::unique_ptr<Not> _not = std::make_unique<Not>();

    public:
        Nor(void) : Gate("Nor")
        {
            addInputPin(1).addInputPin(2).addOutputPin(3);

            this->setLink(1, *_or, 1);
            this->setLink(2, *_or, 2);
            _or->setLink(3, *_not, 1);
            _not->setLink(1, *this, 3);
        }
    };
}
