#pragma once

#include "../gates/Gates.hpp"
#include "IComponent.hpp"

namespace nts {
class Component : virtual public IComponent {
public:
    using PinMap = std::unordered_map<size_t, std::unique_ptr<Pin>>;

protected:
    PinMap _pins;
    std::string _name;

public:
    Component(const std::string& name = "Undefined");

    Component& addInputPin(std::size_t pin);
    Component& addOutputPin(std::size_t pin);

    void setLink(std::size_t pin, IComponent& other,
                 std::size_t otherPin) override;

    Pin& getPin(std::size_t pin);

    const PinMap& getPins(void) const;
    PinMap& getPins(void);

    const std::string& getName(void) const;

    void simulate(void) override;

    void dump(void) const override;

    Tristate compute(std::size_t pin) override;
};

}  // namespace nts
