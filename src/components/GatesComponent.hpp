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
    And(void);
};

class Xor : public DualInputGate {
public:
    Xor(void);
};

class Or : public DualInputGate {
public:
    Or(void);
};

class Not : public Gate {
public:
    Not(void);

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

class FullAdder : public Gate {
private:
    std::unique_ptr<Xor> _xorResult = std::make_unique<Xor>();
    std::unique_ptr<Or> _orResult = std::make_unique<Or>();

    std::unique_ptr<And> _linker1 = std::make_unique<And>();
    std::unique_ptr<And> _linker2 = std::make_unique<And>();
    std::unique_ptr<Xor> _inputLinker = std::make_unique<Xor>();

public:
    FullAdder(const std::string& name="FullAdder");
};

}  // namespace nts
