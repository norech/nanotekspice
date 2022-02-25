#pragma once

#include "Component.hpp"

namespace nts {

class Gate : public Component {
protected:
    Gate(const std::string& name);
};

class DualInputGate : public Gate {
private:
    std::function<Tristate(const Tristate, const Tristate)> _gate;

protected:
    DualInputGate(const std::string& name,
                  std::function<Tristate(const Tristate, const Tristate)> gate);

public:
    Tristate compute(std::size_t pin) override;
};

class And : public DualInputGate {
public:
    And(const std::string& name = "AndGate");
};

class Xor : public DualInputGate {
public:
    Xor(const std::string& name = "XorGate");
};

class Or : public DualInputGate {
public:
    Or(const std::string& name = "OrGate");
};

class Not : public Gate {
public:
    Not(const std::string& name = "NotGate");

    Tristate compute(std::size_t pin) override;
};

template <typename T>
class InputReverter : public Gate {
private:
    std::unique_ptr<T> _gate = std::make_unique<T>();
    std::unique_ptr<Not> _not = std::make_unique<Not>();

public:
    InputReverter(const std::string& name = "InputReverter") : Gate(name) {
        addInputPin(1).addInputPin(2).addOutputPin(3);

        this->setLink(1, *_gate, 1);
        this->setLink(2, *_gate, 2);
        _gate->setLink(3, *_not, 1);
        _not->setLink(2, *this, 3);
    }
};

using Nand = InputReverter<And>;
using Xnor = InputReverter<Xor>;
using Nor = InputReverter<Or>;

}  // namespace nts
