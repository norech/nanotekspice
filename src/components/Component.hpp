#pragma once

#include "../gates/Gates.hpp"
#include "IComponent.hpp"

namespace nts {
class Component : virtual public IComponent {
public:
    using PinMap = std::unordered_map<size_t, std::unique_ptr<Pin>>;

protected:
    PinMap _pins;
    const std::string _name;
    std::size_t _tick = 0;

public:
    Component(const std::string& name);
    ~Component(void) override = default;

    Component& addInputPin(std::size_t pin);
    Component& addOutputPin(std::size_t pin);

    void setLink(std::size_t pin, IComponent& other,
                 std::size_t otherPin) override;

    Pin& getPin(std::size_t pin);

    const PinMap& getPins(void) const;
    PinMap& getPins(void);

    std::size_t getTick(void) const override;

    const std::string& getName(void) const;

    void simulate(std::size_t tick) override;
};

class Component4001 : public Component {
public:
    Component4001(const std::string& name);
    Tristate compute(std::size_t pin) override;
};

class Component4030 : public Component {
public:
    Component4030(const std::string& name);
    Tristate compute(std::size_t pin) override;
};

class Component4069 : public Component {
public:
    Component4069(const std::string& name);
    Tristate compute(std::size_t pin) override;
};

class Component4081 : public Component {
public:
    Component4081(const std::string& name);
    Tristate compute(std::size_t pin) override;
};

class Component4008 : public Component {
public:
    Component4008(const std::string& name);
    Tristate compute(std::size_t pin) override;
};

}  // namespace nts
