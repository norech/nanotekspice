#include "Component.hpp"

namespace nts {

    class Gate : public Component {
    protected:
        Gate(void) : Component("InternalUndefinedGate") {}
    };

    class DualInputGate : public Gate {
    private:
        std::function<Tristate(const Tristate, const Tristate)> _gate;

    protected:
        DualInputGate(std::function<Tristate(const Tristate, const Tristate)> gate) :
        _gate(gate) {
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
        And(void) : DualInputGate(andGate) {}
    };

    class Nand : public DualInputGate {
    public:
        Nand(void) : DualInputGate(nandGate) {}
    };

    class Xor : public DualInputGate {
    public:
        Xor(void) : DualInputGate(xorGate) {}
    };

    class Or : public DualInputGate {
    public:
        Or(void) : DualInputGate(orGate) {}
    };

    class Not : public Gate {
    public:
        Not(void) {
            addInputPin(1).addOutputPin(2);
            setLink(1, *this, 2);
        }

        Tristate compute(std::size_t pin) override {
            if (pin == 2) {
                return _pins[2]->update(notGate(_pins[1]->compute()));
            }
            return _pins[pin]->compute();
        }

    };

    class Nor : public Gate {
    private:
        std::unique_ptr<Or> _or = std::make_unique<Or>();
        std::unique_ptr<Not> _not = std::make_unique<Not>();

    public:
        Nor(const std::string& name="Nor")
        {
            addInputPin(1).addInputPin(2).addOutputPin(3);
            this->setLink(1, *_or, 1);
            this->setLink(2, *_or, 2);
            _or->setLink(3, *_not, 1);
            _not->setLink(2, *this, 3);
        }
    };
}
