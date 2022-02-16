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
    bool _visited = false;
    Tristate _state = Tristate::UNDEFINED;

public:
    Pin(IComponent *component, std::size_t pin, PinType type);
    virtual ~Pin() = default;

    Pin(const Pin &) = delete;

    bool otherIsSelf(const IComponent *other) const;
    bool isLinkedTo(const IComponent *other, std::size_t pin) const;
    void setLink(IComponent *other, std::size_t otherPin);

    PinType getType(void) const;
    Tristate getState(void) const;
    Pin& setState(Tristate state);

    bool isVisited(void) const;
    Pin& visit(void);
    Pin& unvisit(void);

    virtual Tristate compute(void) = 0;

    Tristate update(Tristate state);

};

class InputPin : public Pin {
public:
    InputPin(IComponent *component, std::size_t pin);
    Tristate compute(void) override;
};

class OutputPin : public Pin {
public:
    OutputPin(IComponent *component, std::size_t pin);
    Tristate compute(void) override;
};
}  // namespace nts
