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
            std::function<Tristate(const Tristate, const Tristate)> gate
        );

    public:
        Tristate compute(std::size_t pin) override;
    };

    class And : public DualInputGate {
    public:
        And(void);
    };

    class Nand : public DualInputGate {
    public:
        Nand(void);
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

    class Nor : public Gate {
    private:
        std::unique_ptr<Or> _or = std::make_unique<Or>();
        std::unique_ptr<Not> _not = std::make_unique<Not>();

    public:
        Nor(void);
    };
}
