#pragma once

#include <functional>
#include <memory>

#include "../Tristate.hpp"

namespace nts {

class IComponent;

class Pin {
public:
    using Link = std::pair<IComponent *, std::size_t>;

protected:
    IComponent *_component;
    std::size_t _pin;
    std::vector<Link> _links;
    PinType _type;

public:
    Pin(IComponent *component, std::size_t pin, PinType type);
    virtual ~Pin() = default;

    Pin(const Pin &) = delete;

    virtual void setLink(IComponent *other, std::size_t otherPin) = 0;

    bool otherIsSelf(const IComponent *other) const;
    bool isLinkedTo(const IComponent *other, std::size_t pin) const;

    PinType getType(void) const;
};

class InputPin : public Pin {
public:
    InputPin(IComponent *component, std::size_t pin);
    void setLink(IComponent *other, std::size_t otherPin) override;
};

class OutputPin : public Pin {
public:
    OutputPin(IComponent *component, std::size_t pin);
    void setLink(IComponent *other, std::size_t otherPin) override;
};
}  // namespace nts
