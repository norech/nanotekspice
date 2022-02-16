#pragma once

#include <string>

#include "../Pin/Pin.hpp"
#include "../Tristate.hpp"

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

class Component : public IComponent {
public:
    using PinMap = std::unordered_map<size_t, std::unique_ptr<Pin>>;
private:
    PinMap _pins;
    const std::string _name;

public:
    Component(const std::string& name);
    ~Component(void) override = default;

    Component& addOutputPin(std::size_t pin);
    Component& addInputPin(std::size_t pin);

    void setLink(std::size_t pin, IComponent& other,
            std::size_t otherPin) override;

    Pin& getPin(std::size_t pin);

    const PinMap& getPins(void) const;
    PinMap& getPins(void);

    const std::string& getName(void) const;
};

} // namespace nts
