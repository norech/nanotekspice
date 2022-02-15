#pragma once

#include <string>

#include "../Tristate.hpp"
#include "../Pin/Circuit.hpp"

namespace nts {

class IComponent {
public:
    virtual ~IComponent() = default;

    virtual void simulate(std::size_t tick) = 0;
    virtual Tristate compute(std::size_t pin) = 0;
    virtual void setLink(std::size_t pin, IComponent& other,
                         std::size_t otherPin) = 0;
    virtual void dump() const = 0;
    virtual PinType getPinType(std::size_t pin) const = 0;

private:
};

class Component4001 : public IComponent {
private:
    const std::string _name;

public:
    Component4001(std::string const &name) : _name(name)
    {
        Circuit::addChip(this)
            .addOutputPin(this, 2)
            .addOutputPin(this, 5)
            .addOutputPin(this, 6)
            .addOutputPin(this, 8)
            .addOutputPin(this, 9)
            .addOutputPin(this, 12)
            .addOutputPin(this, 13)
            .addInputPin(this, 3)
            .addInputPin(this, 4)
            .addInputPin(this, 10)
            .addInputPin(this, 11);
    }

    ~Component4001() override = default;

    void simulate(std::size_t tick) override;

    Tristate compute(std::size_t pin) override
    {
        auto chip = Circuit::getInstance()->getChip(this);

        switch (pin) {
        }
    }

    void setLink(std::size_t pin, IComponent& other,
                 std::size_t otherPin) override;
    void dump() const override;
    PinType getPinType(std::size_t pin) const override;
};

}  // namespace nts
